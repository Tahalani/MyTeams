/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** channel
*/

#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "constants.h"
#include "logging_server.h"
#include "packets.h"
#include "server.h"
#include "types.h"

static void send_events(server_t *server, client_t *client, team_t *team, \
    channel_t *channel)
{
    bool sub = false;
    client_t *node = NULL;

    SLIST_FOREACH(node, server->clients, next) {
        sub = is_user_subscribed(node->user, team);
        if (node->user != NULL && (sub || client->user == node->user)) {
            send_channel_packet(node->fd, channel, client->user, \
                COMMAND_CREATE);
        }
    }
}

static void add_new_channel(server_t *server, client_t *client, \
    char *name, char *description)
{
    team_t *team = get_context_team(server, client->use);
    channel_t *channel = NULL;

    if (team == NULL) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, \
            client->use->team_uuid);
        return;
    } else if (!is_user_subscribed(client->user, team)) {
        send_error_packet(client->fd, ERROR_UNAUTHORIZED, NULL);
        return;
    }
    channel = find_channel_in_team_by_name(server, team, name);
    if (channel != NULL) {
        send_error_packet(client->fd, ERROR_ALREADY_EXIST, NULL);
        return;
    }
    channel = new_channel(name, description, team);
    SLIST_INSERT_HEAD(server->data->channels, channel, next);
    server_event_channel_created(team->uuid, channel->uuid, channel->name);
    send_events(server, client, team, channel);
}

void create_channel(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    size_t size = MAX_NAME_LENGTH + MAX_DESCRIPTION_LENGTH;
    ssize_t re = 0;
    ssize_t re2 = 0;
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];

    memset(name, 0, MAX_NAME_LENGTH + 1);
    memset(description, 0, MAX_DESCRIPTION_LENGTH + 1);
    if (packet->data_size != size) {
        send_message_packet(client->fd, 500);
        clear_buffer(client->fd, packet);
        return;
    }
    re = read(client->fd, name, MAX_NAME_LENGTH);
    re2 = read(client->fd, description, MAX_DESCRIPTION_LENGTH);
    if (re != MAX_NAME_LENGTH || re2 != MAX_DESCRIPTION_LENGTH) {
        send_message_packet(client->fd, 500);
    } else
        add_new_channel(server, client, name, description);
}

void list_channels(server_t *server, client_t *client)
{
    team_t *team = get_context_team(server, client->use);
    uuid_t *uuid = NULL;
    channel_t *channel = NULL;

    if (team == NULL) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, \
            client->use->team_uuid);
        return;
    }
    SLIST_FOREACH(uuid, team->channels, next) {
        channel = find_channel_in_team_by_uuid(server, team, uuid->uuid);
        if (channel != NULL) {
            send_channel_packet(client->fd, channel, NULL, COMMAND_LIST);
        }
    }
    send_message_packet(client->fd, 200);
}
