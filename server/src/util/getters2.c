/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** getters2.c
*/

#include <string.h>
#include "server.h"

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
