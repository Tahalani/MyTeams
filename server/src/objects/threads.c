/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** threads.c
*/

#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "types.h"

thread_t *new_thread(char *title, char *message, channel_t *channel)
{
    thread_t *new = malloc(sizeof(thread_t));
    uuid_t *thread_uuid = malloc(sizeof(uuid_t));

    if (new == NULL) {
        fatal_error("malloc failed");
    }
    new->uuid = generate_uuid();
    new->name = strdup(title);
    new->message = strdup(message);
    new->messages = malloc(sizeof(struct message_l));
    if (new->messages == NULL) {
        fatal_error("malloc failed");
    }
    SLIST_INIT(new->messages);
    thread_uuid->uuid = strdup(new->uuid);
    SLIST_INSERT_HEAD(channel->threads, thread_uuid, next);
    return new;
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

thread_t *find_thread_in_channel_by_uuid(server_t *server, channel_t *channel, \
    char *uuid)
{
    uuid_t *node = NULL;
    thread_t *thread = NULL;

    SLIST_FOREACH(node, channel->threads, next) {
        thread = find_thread_by_uuid(server, node->uuid);
        if (thread != NULL && strcmp(thread->uuid, uuid) == 0) {
            return thread;
        }
    }
    return NULL;
}

thread_t *find_thread_in_channel_by_title(server_t *server, \
    channel_t *channel, char *title)
{
    uuid_t *node = NULL;
    thread_t *thread = NULL;

    SLIST_FOREACH(node, channel->threads, next) {
        thread = find_thread_by_uuid(server, node->uuid);
        if (thread != NULL && strcmp(thread->name, title) == 0) {
            return thread;
        }
    }
    return NULL;
}
