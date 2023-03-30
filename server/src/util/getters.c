/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** getters.c
*/

#include <string.h>
#include "server.h"

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
