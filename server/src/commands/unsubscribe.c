/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** unsubscribe
*/

#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "constants.h"
#include "packets.h"
#include "server.h"
#include "types.h"

static void leave_team(client_t *client, team_t *team, uuid_t *uuid)
{
    SLIST_FOREACH(uuid, team->users, next) {
        if (strcmp(uuid->uuid, client->user->uuid) == 0)
            SLIST_REMOVE(team->users, uuid, uuid_s, next);
    }
    send_team_packet(client->fd, team, COMMAND_SUBSCRIBE);
}

static team_t *error_handling_unsubscribe(server_t *server, client_t *client, \
    command_packet_t *packet, char *data)
{
    ssize_t re = 0;
    team_t *team = NULL;

    if (packet->data_size != UUID_LENGTH) {
        send_message_packet(client->fd, 500);
        clear_buffer(client->fd, packet);
        return NULL;
    }
    memset(data, 0, UUID_LENGTH + 1);
    re = read(client->fd, data, UUID_LENGTH);
    if (re != UUID_LENGTH) {
        send_message_packet(client->fd, 500);
        return NULL;
    }
    team = find_team_by_uuid(server, data);
    if (team == NULL) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, data);
        return NULL;
    }
    return team;
}

void unsubscribe_command(server_t *server, client_t *client, \
    command_packet_t *packet)
{
    char data[UUID_LENGTH + 1];
    uuid_t *uuid = NULL;
    team_t *team = NULL;

    team = error_handling_unsubscribe(server, client, packet, data);
    if (team == NULL)
        return;
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
