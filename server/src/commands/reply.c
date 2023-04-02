/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** reply
*/

#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "server.h"

static void add_new_reply(server_t *server, client_t *client, \
    char *title, char *message)
{
    (void) title;
    (void) message;
    (void) client;
    (void) server;
    return;
}

void create_reply(server_t *server, client_t *client, char **data)
{
    if (data[1] == NULL || data[2] == NULL) {
        send_basic_message(client->fd, "400");
        return;
    }
    add_new_reply(server, client, data[1], data[2]);
}

void list_reply(server_t *server, client_t *client)
{
    (void) server;
    (void) client;
    return;
}
