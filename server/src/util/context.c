/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** context.c
*/

#include <string.h>

#include "server.h"
#include "types.h"

void refresh_context_level(server_t *server, client_t *client)
{
    int level = 0;

    get_context_thread(server, client->use);
    if (client->use->thread == NULL) {
        level = 3;
    }
    if (client->use->channel == NULL) {
        level = 2;
    }
    if (client->use->team == NULL) {
        level = 1;
    }
    client->use->use_level = level;
}

void fill_default_use(client_t *client)
{
    client->use->team = NULL;
    client->use->team_uuid = NULL;
    client->use->channel = NULL;
    client->use->channel_uuid = NULL;
    client->use->thread = NULL;
    client->use->thread_uuid = NULL;
    client->use->use_level = 0;
}

void fill_team_use(client_t *client, char **data)
{
    char *team_uuid = strdup(data[0]);

    if (team_uuid == NULL) {
        fatal_error("malloc failed");
    }
    fill_default_use(client);
    client->use->team_uuid = strdup(team_uuid);
}

void fill_channel_use(client_t *client, char **data)
{
    char *channel_uuid = strdup(data[1]);

    if (channel_uuid == NULL) {
        fatal_error("malloc failed");
    }
    fill_team_use(client, data);
    client->use->channel_uuid = strdup(channel_uuid);
}

void fill_thread_use(client_t *client, char **data)
{
    char *thread_uuid = strdup(data[2]);

    if (thread_uuid == NULL) {
        fatal_error("malloc failed");
    }
    fill_channel_use(client, data);
    client->use->thread_uuid = strdup(thread_uuid);
}
