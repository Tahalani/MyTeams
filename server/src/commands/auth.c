/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** auth.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"
#include "server.h"

static
void add_user(server_t **server, client_t **client, char **data, user_t *node)
{
    node = malloc(sizeof(user_t));
    if (node == NULL)
        fatal_error("Malloc failed");
    if (strlen(data[1]) > MAX_NAME_LENGTH) {
        send_basic_message((*client)->fd, "420");
    } else {
        node->username = strdup(data[1]);
        node->uuid = generate_uuid();
        node->fd = (*client)->fd;
        SLIST_INSERT_HEAD((*server)->data->users, node, next);
        send_basic_message((*client)->fd, "220");
    }
    for (int i = 0; data[i] != NULL; i++)
        free(data[i]);
    free(data);
}

void login_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');
    user_t *node = NULL;

    if (data[1] == NULL) {
        send_basic_message(client->fd, "400");
        return;
    }
    SLIST_FOREACH(node, server->data->users, next) {
        if (strcmp(node->username, data[1]) == 0) {
            send_basic_message(client->fd, "220");
            for (int i = 0; data[i] != NULL; i++)
                free(data[i]);
            free(data);
            return;
        }
    }
    add_user(&server, &client, data, node);
}
