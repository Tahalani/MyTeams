/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** channels.c
*/

#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "server.h"
#include "types.h"

channel_t *new_channel(char *name, char *description, team_t *team)
{
    channel_t *new = malloc(sizeof(channel_t));
    uuid_t *channel_uuid = malloc(sizeof(uuid_t));

    if (new == NULL || channel_uuid == NULL) {
        fatal_error("malloc failed");
    }
    new->uuid = generate_uuid();
    new->name = strdup(name);
    new->description = strdup(description);
    new->threads = malloc(sizeof(struct thread_l));
    if (new->threads == NULL) {
        fatal_error("malloc failed");
    }
    SLIST_INIT(new->threads);
    channel_uuid->uuid = strdup(new->uuid);
    SLIST_INSERT_HEAD(team->channels, channel_uuid, next);
    return new;
}

channel_t *find_channel_by_uuid(server_t *server, char *uuid)
{
    channel_t *node = NULL;

    SLIST_FOREACH(node, server->data->channels, next) {
        if (strcmp(node->uuid, uuid) == 0)
            return node;
    }
    return NULL;
}

channel_t *find_channel_in_team_by_uuid(server_t *server, team_t *team, \
    char *uuid)
{
    uuid_t *node = NULL;
    channel_t *channel = NULL;

    SLIST_FOREACH(node, team->channels, next) {
        channel = find_channel_by_uuid(server, node->uuid);
        if (channel != NULL && strcmp(channel->uuid, uuid) == 0) {
            return channel;
        }
    }
    return NULL;
}

channel_t *find_channel_in_team_by_name(server_t *server, team_t *team, \
    char *name)
{
    uuid_t *node = NULL;
    channel_t *channel = NULL;

    SLIST_FOREACH(node, team->channels, next) {
        channel = find_channel_by_uuid(server, node->uuid);
        if (channel != NULL && strcmp(channel->name, name) == 0) {
            return channel;
        }
    }
    return NULL;
}
