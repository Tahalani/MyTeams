/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** context.c
*/

#include <string.h>

#include "server.h"
#include "types.h"

void fill_default_use(client_t *client)
{
    client->use->team_uuid = NULL;
    client->use->channel_uuid = NULL;
    client->use->thread_uuid = NULL;
}

void fill_team_use(client_t *client, char **data)
{
    char *team_uuid = strdup(data[0]);

    fill_default_use(client);
    if (team_uuid == NULL) {
        fatal_error("malloc failed");
    }
    client->use->team_uuid = team_uuid;
}

void fill_channel_use(client_t *client, char **data)
{
    char *channel_uuid = strdup(data[1]);

    fill_team_use(client, data);
    if (channel_uuid == NULL) {
        fatal_error("malloc failed");
    }
    client->use->channel_uuid = channel_uuid;
}

void fill_thread_use(client_t *client, char **data)
{
    char *thread_uuid = strdup(data[2]);

    fill_channel_use(client, data);
    if (thread_uuid == NULL) {
        fatal_error("malloc failed");
    }
    client->use->thread_uuid = thread_uuid;
}
