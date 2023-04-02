/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** channel
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"
#include "server.h"

static void add_new_channel(server_t *server, char *name, char *description)
{
    uuid_t *uuid = malloc(sizeof(uuid_t));
    team_t *team_node = find_team_by_uuid(server, server->use->team_uuid);
    channel_t *new_channel = malloc(sizeof(channel_t));

    if (new_channel == NULL)
        fatal_error("Malloc failed");
    new_channel->uuid = generate_uuid();
    new_channel->name = strdup(name);
    new_channel->description = strdup(description);
    new_channel->threads = malloc(sizeof(struct thread_l));
    SLIST_INIT(new_channel->threads);
    uuid->uuid = strdup(new_channel->uuid);
    SLIST_INSERT_HEAD(server->data->channels, new_channel, next);
    SLIST_INSERT_HEAD(team_node->channels, uuid, next);
}

void create_channel(server_t *server, client_t *client, char **data)
{
    team_t *team = NULL;

    if (data[1] == NULL || data[2] == NULL) {
        send_basic_message(client->fd, "400");
        return;
    }
    team = find_team_by_uuid(server, server->use->team_uuid);
    if (team == NULL) {
        send_basic_message(client->fd, "570");
        return;
    }
    add_new_channel(server, data[1], data[2]);
    send_basic_message(client->fd, "200");
}

void list_channel(server_t *server, client_t *client)
{
    team_t *team = NULL;
    uuid_t *uuid = NULL;
    unsigned int nbr_channel = 0;

    team = find_team_by_uuid(server, server->use->team_uuid);
    if (team == NULL) {
        send_basic_message(client->fd, "570");
        return;
    }
    SLIST_FOREACH(uuid, team->channels, next)
        nbr_channel++;
    uuid = NULL;
    if (nbr_channel == 0) {
        send_basic_message(client->fd, "580");
        return;
    }
    dprintf(client->fd, "%d channel(s) available%s", nbr_channel, CRLF);
    SLIST_FOREACH(uuid, team->channels, next) {
        dprintf(client->fd, "%s (%s)%s", find_channel_by_uuid(server, uuid->uuid)->name, uuid->uuid, CRLF);
    }
    send_basic_message(client->fd, "200");
}
