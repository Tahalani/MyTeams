/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** send.c
*/

#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "constants.h"
#include "logging_server.h"
#include "packets.h"
#include "server.h"
#include "types.h"

static void send_private_message(server_t *server, client_t *client, \
    char *receiver, char *body)
{
    message_t *message = new_message_private(body, receiver, client->user);
    client_t *tmp = NULL;

    SLIST_INSERT_HEAD(server->data->messages, message, next);
    SLIST_FOREACH(tmp, server->clients, next) {
        if (tmp->user != NULL && strcmp(tmp->user->uuid, receiver) == 0) {
            send_reply_packet(tmp->fd, message, NULL, COMMAND_SEND);
        }
    }
    server_event_private_message_sended(client->user->uuid, receiver, body);
}

static user_t *check_read(server_t *server, \
    client_t *client, char *uuid, char *body)
{
    ssize_t re = 0;
    ssize_t re2 = 0;
    user_t *node = NULL;

    re = read(client->fd, uuid, UUID_LENGTH);
    re2 = read(client->fd, body, MAX_BODY_LENGTH);
    if (re != UUID_LENGTH || re2 != MAX_BODY_LENGTH) {
        send_message_packet(client->fd, 500);
        return NULL;
    }
    node = find_user_by_uuid(server, uuid);
    if (node == NULL) {
        send_error_packet(client->fd, ERROR_UNKNOWN_USER, uuid);
        return NULL;
    }
    return node;
}

void send_command(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    size_t size = UUID_LENGTH + MAX_BODY_LENGTH;
    user_t *node = NULL;
    char uuid[UUID_LENGTH + 1];
    char body[MAX_BODY_LENGTH + 1];

    memset(uuid, 0, UUID_LENGTH + 1);
    memset(body, 0, MAX_BODY_LENGTH + 1);
    if (packet->data_size != size) {
        send_message_packet(client->fd, 500);
        clear_buffer(client->fd, packet);
        return;
    }
    node = check_read(server, client, uuid, body);
    if (node == NULL)
        return;
    send_private_message(server, client, uuid, body);
}
