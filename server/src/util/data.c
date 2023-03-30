/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** data.c
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

user_t *new_user(char *username)
{
    user_t *new = malloc(sizeof(user_t));
    if (new == NULL) {
        fatal_error("malloc failed");
    }
    new->uuid = generate_uuid();
    new->username = strdup(username);
    new->teams = NULL;
    return new;
}
