/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** user
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"
#include "server.h"

void users_command(server_t *server, client_t *client, char *input)
{
    user_t *node = NULL;
    char **data = str_to_word(input, ' ');

    if (data[1] != NULL) {
        send_basic_message(client->fd, "400");
        return;
    }
    SLIST_FOREACH(node, server->data->users, next) {
        dprintf(client->fd, "%s%s", node->username, CRLF);
    }
    send_basic_message(client->fd, "200");
}

static void display_user_info(client_t *client, user_t *node)
{
    if (node->username != NULL)
        dprintf(client->fd, "Username : %s%s", node->username, CRLF);
    else
        dprintf(client->fd, "Username : %s%s", "NULL", CRLF);
    if (node->uuid != NULL)
        dprintf(client->fd, "Uuid : %s%s", node->uuid, CRLF);
    else
        dprintf(client->fd, "Uuid : %s%s", "NULL", CRLF);
}

void user_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');
    user_t *node = NULL;

    if (data[1] == NULL || data[2] != NULL) {
        send_basic_message(client->fd, "400");
        return;
    }
    SLIST_FOREACH(node, server->data->users, next) {
        if (strcmp(node->username, data[1]) == 0
        || strcmp(node->uuid, data[1]) == 0) {
            display_user_info(client, node);
            for (int i = 0; data[i] != NULL; i++)
                free(data[i]);
            free(data);
            send_basic_message(client->fd, "200");
            return;
        }
    }
    send_basic_message(client->fd, "410");
}
