/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** team
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

void save_team(team_t *team, int fd)
{
    parsed_team_t parsed;

    memset(&parsed, 0, sizeof(parsed_team_t));
    strcat(parsed.name, team->name);
    strcat(parsed.uuid, team->uuid);
    strcat(parsed.description, team->description);
    write(fd, &parsed, sizeof(parsed_team_t));
}

team_t *load_team(int fd)
{
    team_t *team = malloc(sizeof(team_t));
    parsed_team_t parsed;
    ssize_t re = 0;

    memset(&parsed, 0, sizeof(parsed_team_t));
    re = read(fd, &parsed, sizeof(parsed_team_t));
    if (re != sizeof(parsed_team_t))
        return (NULL);
    team->name = strdup(parsed.name);
    team->uuid = strdup(parsed.uuid);
    team->description = strdup(parsed.description);
    team->channels = malloc(sizeof(struct thread_l));
    team->users = malloc(sizeof(struct user_l));
    SLIST_INIT(team->channels);
    SLIST_INIT(team->users);
    return (team);
}

void relation_team_user(server_t *server, int fd)
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

void load_relation_team_user(server_t *server, int fd)
{
    relation_t *relation = NULL;
    user_t *user = NULL;
    team_t *team = NULL;
    uuid_t *uuid = NULL;

    while ((relation = load_relation(fd))) {
        user = find_user_by_uuid(server, relation->first_uuid);
        team = find_team_by_uuid(server, relation->second_uuid);
        if (user && team) {
            uuid = malloc(sizeof(uuid_t));
            uuid->uuid = strdup(team->uuid);
            SLIST_INSERT_HEAD(user->teams, uuid, next);
            uuid = malloc(sizeof(uuid_t));
            uuid->uuid = strdup(user->uuid);
            SLIST_INSERT_HEAD(team->users, uuid, next);
        }
        free(relation);
    }
}
