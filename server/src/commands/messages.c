/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** messages.c
*/

#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "constants.h"
#include "packets.h"
#include "server.h"
#include "types.h"

static void retrieve_messages(server_t *server, client_t *client, char *uuid)
{
    message_t *node = NULL;
    bool s1 = false;
    bool s2 = false;
    bool s3 = false;
    bool s4 = false;

    SLIST_FOREACH(node, server->data->messages, next) {
        s1 = strcmp(node->author, uuid) == 0;
        s2 = strcmp(node->target, client->user->uuid) == 0;
        s3 = strcmp(node->author, client->user->uuid) == 0;
        s4 = strcmp(node->target, uuid) == 0;
        if ((s1 && s2) || (s3 && s4)) {
            send_reply_packet(client->fd, node, NULL, COMMAND_MESSAGES);
            return;
        }
    }
}

void messages_command(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    char uuid[UUID_LENGTH + 1];

    if (packet->data_size != UUID_LENGTH) {
        send_message_packet(client->fd, 500);
        return;
    }
    memset(uuid, 0, UUID_LENGTH + 1);
    ssize_t re = read(client->fd, uuid, UUID_LENGTH);
    if (re != UUID_LENGTH) {
        send_message_packet(client->fd, 500);
        return;
    }
    retrieve_messages(server, client, uuid);
}
