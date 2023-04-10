/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** channel
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "server.h"
#include "types.h"

static void add_new_channel(server_t *server, team_t *team, \
    char *name, char *description)
{
    uuid_t *uuid = malloc(sizeof(uuid_t));
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
    SLIST_INSERT_HEAD(team->channels, uuid, next);
}

void create_channel(server_t *server, client_t *client, char **data)
{
    team_t *team = client->use->team;

    if (data[1] == NULL || data[2] == NULL) {
        send_basic_message(client->fd, "400");
        return;
    }
    if (team == NULL) {
        send_basic_message(client->fd, "570");
        return;
    }
    add_new_channel(server, client->use->team, data[1], data[2]);
    send_basic_message(client->fd, "200");
}

static void send_list(server_t *server, client_t *client, team_t *team)
{
    uuid_t *uuid = NULL;
    unsigned int nbr_channel = 0;

    SLIST_FOREACH(uuid, team->channels, next)
        nbr_channel++;
    uuid = NULL;
    if (nbr_channel == 0) {
        send_basic_message(client->fd, "580");
        return;
    }
    dprintf(client->fd, "%d channel(s) available%s", nbr_channel, CRLF);
    SLIST_FOREACH(uuid, team->channels, next) {
        dprintf(client->fd, "%s (%s)%s", \
        find_channel_by_uuid(server, uuid->uuid)->name, uuid->uuid, CRLF);
    }
}

void list_channel(server_t *server, client_t *client)
{
    team_t *team = client->use->team;

    if (team == NULL) {
        send_basic_message(client->fd, "570");
        return;
    }
    send_list(server, client, team);
    send_basic_message(client->fd, "200");
}
