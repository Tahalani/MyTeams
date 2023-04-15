/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** channel
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

void save_channel(channel_t *channel, int fd)
{
    parsed_channel_t parsed;

    memset(&parsed, 0, sizeof(parsed_channel_t));
    strcat(parsed.name, channel->name);
    strcat(parsed.uuid, channel->uuid);
    strcat(parsed.description, channel->description);
    write(fd, &parsed, sizeof(parsed_channel_t));
}

channel_t *load_channel(int fd)
{
    channel_t *channel = malloc(sizeof(channel_t));
    parsed_channel_t parsed;

    memset(&parsed, 0, sizeof(parsed_channel_t));
    ssize_t re = read(fd, &parsed, sizeof(parsed_channel_t));
    if (re != sizeof(parsed_channel_t))
        return (NULL);
    channel->name = strdup(parsed.name);
    channel->uuid = strdup(parsed.uuid);
    channel->description = strdup(parsed.description);
    channel->threads = malloc(sizeof(struct thread_l));
    SLIST_INIT(channel->threads);
    return (channel);
}

void relation_channel_team(server_t *server, int fd)
{
    relation_t relation;
    team_t *team = NULL;
    uuid_t *channel = NULL;

    SLIST_FOREACH(team, server->data->teams, next) {
        SLIST_FOREACH(channel, team->channels, next) {
            memset(&relation, 0, sizeof(relation_t));
            strcat(relation.first_uuid, team->uuid);
            strcat(relation.second_uuid, channel->uuid);
            write(fd, &relation, sizeof(relation_t));
        }
    }
}

void load_relation_channel_team(server_t *server, int fd)
{
    relation_t *relation = NULL;

    while ((relation = load_relation(fd))) {
        team_t *team = find_team_by_uuid(server, relation->first_uuid);
        channel_t *channel = find_channel_by_uuid(server, relation->second_uuid);
        if (team && channel) {
            uuid_t *uuid = malloc(sizeof(uuid_t));
            uuid->uuid = strdup(channel->uuid);
            SLIST_INSERT_HEAD(team->channels, uuid, next);
        }
        free(relation);
    }
}
