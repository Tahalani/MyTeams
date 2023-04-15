/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** talk
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "commands.h"
#include "constants.h"
#include "packets.h"
#include "server.h"
#include "types.h"

UNUSED user_t *get_sender(server_t *server, client_t *client)
{
    user_t *node = NULL;

    SLIST_FOREACH(node, server->data->users, next) {
        if (node->fd == client->fd)
            return node;
    }
    return NULL;
}

static void fill_message_struct(server_t *server, client_t *client, char **data)
{
    message_t *message = malloc(sizeof(message_t));

    if (message == NULL)
        fatal_error("Malloc failed");
    message->sender = client->user;
    message->body = strdup(data[2]);
    message->created_at = time(NULL);
    SLIST_INSERT_HEAD(server->data->messages, message, next);
}

void send_command(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    char *input = "";
    char **data = str_to_word(input, ' ');
    user_t *node = NULL;

    if (data[1] == NULL || data[2] == NULL || data[3] != NULL) {
        send_basic_message(client->fd, "400");
        free_array(data);
        return;
    }
    node = find_user_by_uuid(server, data[1]);
    if (node == NULL || node->fd == -1) {
        send_basic_message(client->fd, "410");
        free_array(data);
        return;
    }
    fill_message_struct(server, client, data);
    dprintf(node->fd, "%s: %s%s",
        get_username_client(server, client), data[2], CRLF);
}

void messages_command(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    char *input = "";
    message_t *node = NULL;
    char **data = str_to_word(input, ' ');

    if (data[1] == NULL && data[2] != NULL) {
        send_basic_message(client->fd, "400");
        free_array(data);
        return;
    }
    SLIST_FOREACH(node, server->data->messages, next) {
        if (strcmp(node->sender->uuid, data[1]) == 0)
            dprintf(client->fd, "%s: %s%s",
                node->sender->username, node->body, CRLF);
    }
    send_basic_message(client->fd, "200");
    free_array(data);
}
