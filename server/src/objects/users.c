/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** users.c
*/

#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "types.h"

user_t *new_user(char *username, int fd)
{
    user_t *new = malloc(sizeof(user_t));

    if (new == NULL) {
        fatal_error("malloc failed");
    }
    new->uuid = generate_uuid();
    new->username = strdup(username);
    new->fd = fd;
    new->teams = malloc(sizeof(struct team_l));
    if (new->teams == NULL) {
        fatal_error("malloc failed");
    }
    SLIST_INIT(new->teams);
    return (new);
}

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
