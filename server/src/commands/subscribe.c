/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** subscribe.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <unistd.h>

#include "constants.h"
#include "logging_server.h"
#include "packets.h"
#include "server.h"
#include "types.h"

static void join_team(client_t *client, team_t *team)
{
    uuid_t *uuid = malloc(sizeof(uuid_t));
    uuid_t *uuid2 = malloc(sizeof(uuid_t));

    if (team == NULL || uuid == NULL || uuid2 == NULL) {
        send_basic_message(client->fd, "421");
        return;
    }
    uuid->uuid = team->uuid;
    SLIST_INSERT_HEAD(client->user->teams, uuid, next);
    uuid2->uuid = client->user->uuid;
    SLIST_INSERT_HEAD(team->users, uuid2, next);
    send_team_packet(client->fd, team, COMMAND_SUBSCRIBE);
}

void subscribe_command(server_t *server, client_t *client, \
    command_packet_t *packet)
{
    char uuid[UUID_LENGTH + 1];
    team_t *team = NULL;
    ssize_t re = 0;

    if (packet->data_size != UUID_LENGTH) {
        send_message_packet(client->fd, 500);
        clear_buffer(client->fd, packet);
        return;
    }
    memset(uuid, 0, UUID_LENGTH + 1);
    re = read(client->fd, uuid, UUID_LENGTH);
    if (re != UUID_LENGTH) {
        send_message_packet(client->fd, 500);
        return;
    }
    team = find_team_by_uuid(server, uuid);
    if (team == NULL) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, uuid);
        return;
    }
    team = find_team_by_uuid(server, uuid);
    join_team(client, team);
}

static void leave_team(client_t *client, team_t *team, uuid_t *uuid)
{
    SLIST_FOREACH(uuid, team->users, next) {
        if (strcmp(uuid->uuid, client->user->uuid) == 0)
            SLIST_REMOVE(team->users, uuid, uuid_s, next);
    }
    send_team_packet(client->fd, team, COMMAND_SUBSCRIBE);
}

void unsubscribe_command(server_t *server, client_t *client, \
    command_packet_t *packet)
{
    char data[UUID_LENGTH + 1];
    team_t *team = NULL;
    uuid_t *uuid = NULL;
    ssize_t re = 0;

    if (packet->data_size != UUID_LENGTH) {
        send_message_packet(client->fd, 500);
        clear_buffer(client->fd, packet);
        return;
    }
    memset(data, 0, UUID_LENGTH + 1);
    re = read(client->fd, data, UUID_LENGTH);
    if (re != UUID_LENGTH) {
        send_message_packet(client->fd, 500);
        return;
    }
    team = find_team_by_uuid(server, data);
    if (team == NULL) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, data);
        return;
    }
    SLIST_FOREACH(uuid, client->user->teams, next) {
        if (strcmp(uuid->uuid, data) == 0)
            SLIST_REMOVE(client->user->teams, uuid, uuid_s, next);
    }
    uuid = NULL;
    SLIST_FOREACH(team, server->data->teams, next) {
        if (strcmp(team->uuid, data) == 0)
            leave_team(client, team, uuid);
    }
}

static int read_args(client_t *client, char *uuid, command_packet_t *packet)
{
    ssize_t re = 0;

    if (packet->data_size != UUID_LENGTH && packet->data_size != 0) {
        send_message_packet(client->fd, 500);
        clear_buffer(client->fd, packet);
        return -1;
    }
    if (packet->data_size == UUID_LENGTH) {
        re = read(client->fd, uuid, UUID_LENGTH);
        if (re != UUID_LENGTH) {
            send_message_packet(client->fd, 500);
            return -1;
        }
    }
    return packet->data_size != 0;
}

void subscribed_command(server_t *server, client_t *client, \
    command_packet_t *packet)
{
    team_t *team = NULL;
    uuid_t *uuid = NULL;
    char data[UUID_LENGTH + 1];
    int len = 0;

    memset(data, 0, UUID_LENGTH + 1);
    len = read_args(client, data, packet);
    if (len == -1)
        return;
    if (len == 0) {
        SLIST_FOREACH(uuid, client->user->teams, next)
            send_team_packet(client->fd,
            find_team_by_uuid(server, uuid->uuid), COMMAND_SUBSCRIBED);
    } else {
        team = find_team_by_uuid(server, data);
        if (team == NULL) {
            send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, data);
            return;
        }
        SLIST_FOREACH(uuid, team->users, next)
            send_user_packet(client->fd,
            find_user_by_uuid(server, uuid->uuid), COMMAND_SUBSCRIBED);
    }
    send_message_packet(client->fd, 200);
}
