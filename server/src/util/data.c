/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** data.c
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

user_t *new_user(char *username, int fd)
{
    user_t *new = malloc(sizeof(user_t));
    if (new == NULL) {
        fatal_error("malloc failed");
    }
    new->uuid = generate_uuid();
    new->username = strdup(username);
    new->fd = fd;
    new->fd = -1;
    new->teams = malloc(sizeof(team_t));
    SLIST_INIT(new->teams);
    return (new);
}
