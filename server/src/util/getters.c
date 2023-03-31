/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** getters.c
*/

#include <string.h>
#include "server.h"

user_t *find_user_by_uuid(server_t *server, char *uuid)
{
    user_t *user = NULL;

    SLIST_FOREACH(user, server->data->users, next) {
        if (strcmp(user->uuid, uuid) == 0) {
            return user;
        }
    }
    return NULL;
}

user_t *find_user_by_name(server_t *server, char *name)
{
    user_t *user = NULL;

    SLIST_FOREACH(user, server->data->users, next) {
        if (strcmp(user->username, name) == 0) {
            return user;
        }
    }
    return NULL;
}

team_t *find_team_by_uuid(server_t *server, char *uuid)
{
    team_t *team = NULL;

    SLIST_FOREACH(team, server->data->teams, next) {
        if (strcmp(team->uuid, uuid) == 0)
            return team;
    }
    return NULL;
}
