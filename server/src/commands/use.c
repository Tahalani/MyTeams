/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** use
*/

#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "server.h"

static void fill_default_use(server_t *server, client_t *client)
{
    server->use->team_uuid = NULL;
    server->use->channel_uuid = NULL;
    server->use->thread_uuid = NULL;
    send_basic_message(client->fd, "200");
}

static void fill_team_use(server_t *server, client_t *client, char **data)
{
    server->use->team_uuid = strdup(data[1]);
    server->use->channel_uuid = NULL;
    server->use->thread_uuid = NULL;
    send_basic_message(client->fd, "200");
}

static void fill_channel_use(server_t *server, client_t *client, char **data)
{
    server->use->team_uuid = strdup(data[1]);
    server->use->channel_uuid = strdup(data[2]);
    server->use->thread_uuid = NULL;
    send_basic_message(client->fd, "200");
}

static void fill_thread_use(server_t *server, client_t *client, char **data)
{
    server->use->team_uuid = strdup(data[1]);
    server->use->channel_uuid = strdup(data[2]);
    server->use->thread_uuid = strdup(data[3]);
    send_basic_message(client->fd, "200");
}

void use_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');
    if (data[1] == NULL) {
        fill_default_use(server, client);
        free_array(data);
        return;
    } if (data[2] == NULL) {
        fill_team_use(server, client, data);
        free_array(data);
        return;
    } if (data[3] == NULL) {
        fill_channel_use(server, client, data);
        free_array(data);
        return;
    } if (data[4] == NULL) {
        fill_thread_use(server, client, data);
        free_array(data);
        return;
    }
    send_basic_message(client->fd, "400");
    free_array(data);
}
