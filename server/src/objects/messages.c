/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** messages.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <time.h>

#include "server.h"
#include "types.h"

message_t *new_message_thread(char *body, thread_t *thread, user_t *user)
{
    message_t *new = malloc(sizeof(message_t));
    uuid_t *message_uuid = malloc(sizeof(uuid_t));

    if (new == NULL || message_uuid == NULL) {
        fatal_error("malloc failed");
    }
    new->uuid = generate_uuid();
    new->body = strdup(body);
    new->author = strdup(user->uuid);
    new->target = thread->uuid;
    new->created_at = time(NULL);
    new->is_private = false;
    message_uuid->uuid = strdup(new->uuid);
    SLIST_INSERT_HEAD(thread->messages, message_uuid, next);
    return new;
}

message_t *new_message_private(char *body, char *receiver, user_t *user)
{
    message_t *new = malloc(sizeof(message_t));

    if (new == NULL) {
        fatal_error("malloc failed");
    }
    new->uuid = generate_uuid();
    new->body = strdup(body);
    new->author = strdup(user->uuid);
    new->target = strdup(receiver);
    new->created_at = time(NULL);
    new->is_private = true;
    return new;
}

message_t *find_message_by_uuid(server_t *server, char *uuid)
{
    message_t *message = NULL;

    SLIST_FOREACH(message, server->data->messages, next) {
        if (strcmp(message->uuid, uuid) == 0)
            return message;
    }
    return NULL;
}

message_t *find_message_in_thread_by_uuid(server_t *server, thread_t *thread, \
    char *uuid)
{
    uuid_t *node = NULL;
    message_t *message = NULL;

    SLIST_FOREACH(node, thread->messages, next) {
        message = find_message_by_uuid(server, node->uuid);
        if (message != NULL && strcmp(message->uuid, uuid) == 0) {
            return message;
        }
    }
    return NULL;
}
