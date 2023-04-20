/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** teams_rel.c
*/

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "database.h"
#include "server.h"
#include "types.h"

static void load_user_relations(server_t *server, int fd)
{
    relation_t *relation = NULL;
    user_t *user = NULL;
    team_t *team = NULL;
    uuid_t *uuid = NULL;

    while ((relation = load_relation(fd))) {
        user = find_user_by_uuid(server, relation->first_uuid);
        team = find_team_by_uuid(server, relation->second_uuid);
        if (user != NULL && team != NULL) {
            uuid = malloc(sizeof(uuid_t));
            ensure_allocated(uuid);
            uuid->uuid = strdup(team->uuid);
            SLIST_INSERT_HEAD(user->teams, uuid, next);
            uuid = malloc(sizeof(uuid_t));
            ensure_allocated(uuid);
            uuid->uuid = strdup(user->uuid);
            SLIST_INSERT_HEAD(team->users, uuid, next);
        }
        free(relation);
    }
}

void load_team_user_relations(server_t *server)
{
    int fd = open(DB_FILE_REL_TEAMS_USERS, O_RDONLY);

    if (fd == -1) {
        return;
    }
    load_user_relations(server, fd);
    close(fd);
}

static void save_user_relations(server_t *server, int fd)
{
    relation_t relation;
    user_t *user = NULL;
    uuid_t *team = NULL;

    SLIST_FOREACH(user, server->data->users, next) {
        SLIST_FOREACH(team, user->teams, next) {
            memset(&relation, 0, sizeof(relation_t));
            strcat(relation.first_uuid, user->uuid);
            strcat(relation.second_uuid, team->uuid);
            write(fd, &relation, sizeof(relation_t));
        }
    }
}

void save_team_user_relations(server_t *server)
{
    int fd = open(DB_FILE_REL_TEAMS_USERS, O_RDWR | O_CREAT, 0777);

    if (fd == -1) {
        return;
    }
    save_user_relations(server, fd);
    close(fd);
}
