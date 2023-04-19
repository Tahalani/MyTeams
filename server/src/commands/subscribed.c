/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** subscribed
*/

#include <stdbool.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "constants.h"
#include "packets.h"
#include "server.h"
#include "types.h"

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

static bool display_user_in_team(server_t *server, client_t *client, \
    char *data)
{
    team_t *team = NULL;
    uuid_t *uuid = NULL;

    team = find_team_by_uuid(server, data);
    if (team == NULL) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, data);
        return false;
    }
    SLIST_FOREACH(uuid, team->users, next)
        send_user_packet(client->fd,
        find_user_by_uuid(server, uuid->uuid), COMMAND_SUBSCRIBED);
    return true;
}

void subscribed_command(server_t *server, client_t *client, \
    command_packet_t *packet)
{
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
        if (display_user_in_team(server, client, data) == false)
            return;
    }
    send_message_packet(client->fd, 200);
}
