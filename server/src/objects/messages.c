/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** messages.c
*/

#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <time.h>

#include "server.h"
#include "types.h"

message_t *new_message(char *body, thread_t *thread, user_t *user)
{
    message_t *new = malloc(sizeof(message_t));
    uuid_t *message_uuid = malloc(sizeof(uuid_t));

    if (new == NULL || message_uuid == NULL) {
        fatal_error("malloc failed");
    }
    new->uuid = generate_uuid();
    new->body = strdup(body);
    new->sender = user;
    new->created_at = time(NULL);
    message_uuid->uuid = strdup(new->uuid);
    SLIST_INSERT_HEAD(thread->messages, message_uuid, next);
    return new;
}
