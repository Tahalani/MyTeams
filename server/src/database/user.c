/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** user
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

void save_user(user_t *user, int fd)
{
    parsed_user_t parsed;

    memset(&parsed, 0, sizeof(parsed_user_t));
    strcat(parsed.username, user->username);
    strcat(parsed.uuid, user->uuid);
    write(fd, &parsed, sizeof(parsed_user_t));
}

user_t *load_user(int fd)
{
    user_t *user = malloc(sizeof(user_t));
    parsed_user_t parsed;

    memset(&parsed, 0, sizeof(parsed_user_t));
    ssize_t re = read(fd, &parsed, sizeof(parsed_user_t));
    if (re != sizeof(parsed_user_t))
        return (NULL);
    user->username = strdup(parsed.username);
    user->uuid = strdup(parsed.uuid);
    user->fd = -1;
    user->teams = malloc(sizeof(struct team_l));
    SLIST_INIT(user->teams);
    return (user);
}
