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
    client->use->team = NULL;
    client->use->team_uuid = NULL;
    client->use->channel = NULL;
    client->use->channel_uuid = NULL;
    client->use->thread = NULL;
    client->use->thread_uuid = NULL;
    client->use->not_found = 0;
}

void fill_team_use(client_t *client, char **data)
{
    char *team_uuid = strdup(data[0]);

    if (team_uuid == NULL) {
        fatal_error("malloc failed");
    }
    fill_default_use(client);
    client->use->team_uuid = team_uuid;
}

team_t *fill_channel_use(server_t *server, client_t *client, char **data)
{
    team_t *team_check = NULL;
    channel_t *channel_check = NULL;
    char *channel_uuid = strdup(data[1]);

    if (channel_uuid == NULL) {
        fatal_error("malloc failed");
    }
    fill_team_use(client, data);
    client->use->channel_uuid = channel_uuid;
    team_check = find_team_by_uuid(server, client->use->team_uuid);
    if (team_check == NULL) {
        client->use->not_found = 1;
        return NULL;
    }
    channel_check = find_channel_in_team_by_uuid(server,
        team_check, client->use->channel_uuid);
    if (channel_check == NULL) {
        client->use->not_found = 2;
        return NULL;
    }
    return team_check;
}

void fill_thread_use(server_t *server, client_t *client, char **data)
{
    team_t *team = NULL;
    channel_t *channel_check = NULL;
    char *thread_uuid = strdup(data[2]);

    if (thread_uuid == NULL) {
        fatal_error("malloc failed");
    }
    team = fill_channel_use(server, client, data);
    client->use->thread_uuid = thread_uuid;
    if (team == NULL)
        return;
    channel_check = find_channel_in_team_by_uuid(server,
        team, client->use->channel_uuid);
    if (channel_check == NULL) {
        client->use->not_found = 2;
        return;
    }
    if (find_thread_in_channel_by_uuid(server,
        channel_check, client->use->thread_uuid) == NULL)
        client->use->not_found = 3;
}
