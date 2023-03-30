/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** talk
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"
#include "server.h"

user_t *get_sender(server_t *server, client_t *client)
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
    message->sender = get_sender(server, client);
    message->content = strdup(data[2]);
    message->time = get_time();
    SLIST_INSERT_HEAD(server->data->messages, message, next);
}

void send_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');
    user_t *node = NULL;

    if (data[1] == NULL || data[2] == NULL || data[3] != NULL) {
        send_basic_message(client->fd, "400");
        free_array(data);
        return;
    }
    node = find_user_by_uuid(server, data[1]);
    if (node == NULL)
        node = find_user_by_name(server, data[1]);
    if (node == NULL) {
        send_basic_message(client->fd, "410");
        free_array(data);
        return;
    }
    fill_message_struct(server, client, data);
    dprintf(node->fd, "%s: %s%s",
        get_username_client(server, client), data[2], CRLF);
}
