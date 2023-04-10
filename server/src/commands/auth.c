/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** auth.c
*/

#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/queue.h>

#include "logging_server.h"
#include "server.h"
#include "constants.h"
#include "packets.h"
#include "types.h"

static void logged_in_event(client_t *client, bool new)
{
    send_user_packet(client->fd, client->user, COMMAND_LOGIN);
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
    char buffer[MAX_NAME_LENGTH + 1];
    ssize_t re = 0;

    memset(buffer, 0, MAX_NAME_LENGTH + 1);
    re = read(client->fd, &buffer, MAX_NAME_LENGTH);
    if (re != MAX_NAME_LENGTH) {
        send_message_packet(client->fd, 500);
        return;
    }
    connect_user(server, client, buffer);
}

void logout_command(UNUSED server_t *server, client_t *client, \
    UNUSED char *input)
{
    if (client->user == NULL) {
        send_message_packet(client->fd, 500);
        return;
    }
    send_user_packet(client->fd, client->user, COMMAND_LOGOUT);
    server_event_user_logged_out(client->user->uuid);
    client->user->fd = -1;
    client->user = NULL;
}
