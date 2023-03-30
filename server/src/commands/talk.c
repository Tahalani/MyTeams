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
            dprintf(node->fd, "%s: %s%s",
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
