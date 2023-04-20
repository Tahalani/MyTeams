/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** user
*/

#include <stdbool.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "constants.h"
#include "packets.h"
#include "server.h"
#include "types.h"

void users_command(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    user_t *node = NULL;
    bool online = false;

    SLIST_FOREACH(node, server->data->users, next) {
        online = is_user_connected(server, node);
        send_user_packet(client->fd, node, online, COMMAND_USERS);
    }
    send_message_packet(client->fd, 200);
}

static bool is_read(client_t *client, char *uuid)
{
    ssize_t re = 0;

    re = read(client->fd, uuid, UUID_LENGTH);
    if (re != UUID_LENGTH) {
        send_message_packet(client->fd, 500);
        return false;
    }
    return true;
}

void user_command(server_t *server, client_t *client, \
    command_packet_t *packet)
{
    char uuid[UUID_LENGTH + 1];
    user_t *node = NULL;
    bool online = false;

    if (packet->data_size != UUID_LENGTH) {
        send_message_packet(client->fd, 500);
        return;
    }
    memset(uuid, 0, UUID_LENGTH + 1);
    if (is_read(client, uuid) == false)
        return;
    SLIST_FOREACH(node, server->data->users, next) {
        if (strcmp(node->uuid, uuid) == 0) {
            online = is_user_connected(server, node);
            send_user_packet(client->fd, node, online, COMMAND_USER);
            return;
        }
    }
    send_error_packet(client->fd, ERROR_UNKNOWN_USER, uuid);
}
