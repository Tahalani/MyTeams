/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** subscribe.c
*/

#include <stdlib.h>
#include <string.h>
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
        return;
    }
    uuid->uuid = team->uuid;
    SLIST_INSERT_HEAD(client->user->teams, uuid, next);
    uuid2->uuid = client->user->uuid;
    SLIST_INSERT_HEAD(team->users, uuid2, next);
    send_team_packet(client->fd, team, NULL, COMMAND_SUBSCRIBE);
    server_event_user_subscribed(team->uuid, client->user->uuid);
}

static void check_team(server_t *server, client_t *client, char *uuid)
{
    team_t *team = NULL;

    team = find_team_by_uuid(server, uuid);
    if (team == NULL) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, uuid);
        return;
    }
    team = find_team_by_uuid(server, uuid);
    join_team(client, team);
}

void subscribe_command(server_t *server, client_t *client, \
    command_packet_t *packet)
{
    char uuid[UUID_LENGTH + 1];
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
    check_team(server, client, uuid);
}
