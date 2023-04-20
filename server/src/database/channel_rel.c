/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** channel_rel.c
*/

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "database.h"
#include "server.h"
#include "types.h"

static void load_channel_relations(server_t *server, int fd)
{
    relation_t *relation = NULL;
    team_t *team = NULL;
    channel_t *channel = NULL;
    uuid_t *uuid = NULL;

    while ((relation = load_relation(fd))) {
        team = find_team_by_uuid(server, relation->first_uuid);
        channel = find_channel_by_uuid(server, relation->second_uuid);
        if (team != NULL && channel != NULL) {
            uuid = malloc(sizeof(uuid_t));
            ensure_allocated(uuid);
            uuid->uuid = strdup(channel->uuid);
            SLIST_INSERT_HEAD(team->channels, uuid, next);
        }
        free(relation);
    }
}

void load_team_channel_relations(server_t *server)
{
    int fd = open(DB_FILE_REL_TEAMS_CHANNELS, O_RDONLY);

    if (fd == -1) {
        return;
    }
    load_channel_relations(server, fd);
    close(fd);
}

void save_channel_relations(server_t *server, int fd)
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

void save_team_channel_relations(server_t *server)
{
    int fd = open(DB_FILE_REL_TEAMS_CHANNELS, \
        O_RDWR | O_CREAT, 0777);

    if (fd == -1) {
        return;
    }
    save_channel_relations(server, fd);
    close(fd);
}
