/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** talk
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

message_t *get_right_message(server_t *server, char *uuid)
{
    message_t *node = NULL;

    SLIST_FOREACH(node, server->data->messages, next) {
        if (strcmp(node->sender->uuid, uuid) == 0)
            return node;
    }
    return NULL;
}

static message_t *fill_message_struct(server_t *server, \
    client_t *client, char *body)
{
    message_t *message = malloc(sizeof(message_t));

    if (message == NULL)
        fatal_error("Malloc failed");
    message->uuid = generate_uuid();
    message->sender = client->user;
    message->body = strdup(body);
    message->created_at = time(NULL);
    SLIST_INSERT_HEAD(server->data->messages, message, next);
    return message;
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
    if (node == NULL || node->fd == -1) {
        send_error_packet(client->fd, ERROR_UNKNOWN_USER, NULL);
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
    server_event_private_message_sended(client->user->uuid, uuid, body);
    send_reply_packet(node->fd,
    fill_message_struct(server, client, body), COMMAND_SEND);
}

void messages_command(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    char uuid[UUID_LENGTH + 1];
    message_t *node = NULL;

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
    SLIST_FOREACH(node, server->data->messages, next) {
        if (strcmp(node->sender->uuid, uuid) == 0) {
            send_reply_packet(client->fd, node, COMMAND_MESSAGES);
            return;
        }
    }
    send_error_packet(client->fd, ERROR_UNKNOWN_USER, NULL);
}
