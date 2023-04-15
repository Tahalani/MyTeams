/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** teams.c
*/

#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "types.h"

team_t *new_team(char *name, char *description)
{
    team_t *new = malloc(sizeof(team_t));

    if (new == NULL) {
        fatal_error("malloc failed");
    }
    new->uuid = generate_uuid();
    new->name = strdup(name);
    new->description = strdup(description);
    new->users = malloc(sizeof(struct user_l));
    new->channels = malloc(sizeof(struct thread_l));
    if (new->users == NULL || new->channels == NULL) {
        fatal_error("malloc failed");
    }
    SLIST_INIT(new->users);
    SLIST_INIT(new->channels);
    return new;
}

team_t *find_team_by_uuid(server_t *server, char *uuid)
{
    team_t *team = NULL;

    SLIST_FOREACH(team, server->data->teams, next) {
        if (strcmp(team->uuid, uuid) == 0) {
            return team;
        }
    }
    return NULL;
}

team_t *find_team_by_name(server_t *server, char *name)
{
    team_t *team = NULL;

    SLIST_FOREACH(team, server->data->teams, next) {
        if (strcmp(team->name, name) == 0) {
            return team;
        }
    }
    return NULL;
}
