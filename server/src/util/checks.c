/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** checks.c
*/

#include <stdbool.h>
#include <string.h>
#include <sys/queue.h>

#include "types.h"

bool is_user_connected(server_t *server, user_t *user)
{
    client_t *client = NULL;

    SLIST_FOREACH(client, server->clients, next) {
        if (client->user == user) {
            return true;
        }
    }
    return false;
}

bool is_user_subscribed(user_t *user, team_t *team)
{
    uuid_t *uuid = NULL;

    if (user == NULL) {
      return false;
    }
    SLIST_FOREACH(uuid, team->users, next) {
        if (strcmp(uuid->uuid, user->uuid) == 0)
            return true;
    }
    return false;
}
