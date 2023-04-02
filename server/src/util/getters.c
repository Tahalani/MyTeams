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
    team_t *node = NULL;

    SLIST_FOREACH(node, server->data->teams, next) {
        if (strcmp(node->uuid, uuid) == 0)
            return node;
    }
    return NULL;
}

channel_t *find_channel_by_uuid(server_t *server, char *uuid)
{
    channel_t *node = NULL;

    SLIST_FOREACH(node, server->data->channels, next) {
        if (strcmp(node->uuid, uuid) == 0)
            return node;
    }
    return NULL;
}

thread_t *find_thread_by_uuid(server_t *server, char *uuid)
{
    thread_t *node = NULL;

    SLIST_FOREACH(node, server->data->threads, next) {
        if (strcmp(node->uuid, uuid) == 0)
            return node;
    }
    return NULL;
}
