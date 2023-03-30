/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** auth.c
*/

#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "logging_server.h"
#include "server.h"

static void logged_in_event(client_t *client, bool new)
{
    dprintf(client->fd, "200 Logged in as %s (%s)%s", \
        client->user->username, client->user->uuid, CRLF);
    if (new) {
        server_event_user_created(client->user->uuid, client->user->username);
    } else {
        server_event_user_loaded(client->user->uuid, client->user->username);
    }
}

static void connect_user(server_t *server, client_t *client, \
    user_t *user, char *name)
{
    // TODO: Add fd
    if (user != NULL) {
        client->user = user;
        logged_in_event(client, false);
        return;
    }
    user = new_user(name);
    SLIST_INSERT_HEAD(server->data->users, user, next);
    client->user = user;
    logged_in_event(client, true);
}

void login_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');
    user_t *user = NULL;

    if (data[1] == NULL || data[2] != NULL) {
        send_basic_message(client->fd, "400");
        free_array(data);
        return;
    }
    user = find_user_by_name(server, data[1]);
    if (strlen(data[1]) > MAX_NAME_LENGTH) {
        send_basic_message(client->fd, "420");
        free_array(data);
        return;
    }
    connect_user(server, client, user, data[1]);
    free_array(data);
}

void logout_command (UNUSED server_t *server, client_t *client, \
    UNUSED char *input)
{
    send_basic_message(client->fd, "221");
    client->user->fd = -1;
    client->user = NULL;
}
