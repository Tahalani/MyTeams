/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** user
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

void users_command(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    user_t *node = NULL;

    SLIST_FOREACH(node, server->data->users, next) {
        send_user_packet(client->fd, node, COMMAND_USERS);
    }
    send_message_packet(client->fd, 200);
}

void user_command(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    char uuid[UUID_LENGTH + 1];
    user_t *node = NULL;
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
    SLIST_FOREACH(node, server->data->users, next) {
        if (strcmp(node->uuid, uuid) == 0)
            send_user_packet(client->fd, node, COMMAND_USER);
    }
    send_message_packet(client->fd, 200);
}
