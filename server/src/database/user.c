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

#include "database.h"
#include "logging_server.h"
#include "types.h"

static user_t *load_user(int fd)
{
    user_t *user = malloc(sizeof(user_t));
    parsed_user_t parsed;
    ssize_t re = 0;

    memset(&parsed, 0, sizeof(parsed_user_t));
    re = read(fd, &parsed, sizeof(parsed_user_t));
    if (re != sizeof(parsed_user_t))
        return (NULL);
    user->username = strdup(parsed.username);
    user->uuid = strdup(parsed.uuid);
    user->fd = -1;
    user->teams = malloc(sizeof(struct team_l));
    SLIST_INIT(user->teams);
    return (user);
}

void load_users(server_t *server)
{
    user_t *user = NULL;
    int fd_user = open(DB_FILE_USERS, O_RDONLY);

    if (fd_user == -1)
        return;
    user = load_user(fd_user);
    while (user != NULL) {
        SLIST_INSERT_HEAD(server->data->users, user, next);
        server_event_user_loaded(user->uuid, user->username);
        user = load_user(fd_user);
    }
    close(fd_user);
}

void save_user(user_t *user, int fd)
{
    parsed_user_t parsed;

    memset(&parsed, 0, sizeof(parsed_user_t));
    strcat(parsed.username, user->username);
    strcat(parsed.uuid, user->uuid);
    write(fd, &parsed, sizeof(parsed_user_t));
}
