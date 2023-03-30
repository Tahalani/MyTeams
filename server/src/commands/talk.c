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

void display_time(int fd)
{
    time_t current_time;
    struct tm timestamp;
    char buffer[80];

    time(&current_time);
    timestamp = *localtime(&current_time);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", &timestamp);
    dprintf(fd, "%s", buffer);
}

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
        return;
    }
    SLIST_FOREACH(node, server->data->users, next) {
        if (strcmp(node->username, data[1]) == 0
        || strcmp(node->uuid, data[1]) == 0) {
            fill_message_struct(server, client, data);
            display_time(node->fd);
            dprintf(node->fd, " - %s: %s%s",
            get_username_client(server, client), data[2], CRLF);
            for (int i = 0; data[i] != NULL; i++)
                free(data[i]);
            free(data);
            send_basic_message(client->fd, "200");
            return;
        }
    }
    send_basic_message(client->fd, "410");
}
