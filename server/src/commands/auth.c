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
    send_user_packet(client->fd, client->user);
    if (new) {
        server_event_user_created(client->user->uuid, client->user->username);
    }
    server_event_user_logged_in(client->user->uuid);
}

static void connect_user(server_t *server, client_t *client, char *name)
{
    user_t *user = find_user_by_name(server, name);

    if (user != NULL) {
        client->user = user;
        logged_in_event(client, false);
        return;
    }
    user = new_user(name, client->fd);
    SLIST_INSERT_HEAD(server->data->users, user, next);
    client->user = user;
    user->fd = client->fd;
    logged_in_event(client, true);
}

void login_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');

    if (array_len(data) != 2) {
        send_message_packet(client->fd, 400);
        free_array(data);
        return;
    }
    if (strlen(data[1]) > MAX_NAME_LENGTH) {
        send_message_packet(client->fd, 420);
        free_array(data);
        return;
    }
    connect_user(server, client, data[1]);
    free_array(data);
}

void logout_command (UNUSED server_t *server, client_t *client, \
    UNUSED char *input)
{
    send_message_packet(client->fd, 221);
    server_event_user_logged_out(client->user->uuid);
    client->user->fd = -1;
    client->user = NULL;
}
