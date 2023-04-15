/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** message
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

void save_message(message_t *message, int fd)
{
    parsed_message_t parsed;

    memset(&parsed, 0, sizeof(parsed_message_t));
    strcat(parsed.uuid, message->uuid);
    strcat(parsed.uuid_user, message->sender->uuid);
    strcat(parsed.body, message->body);
    write(fd, &parsed, sizeof(parsed_message_t));
}

message_t *load_message(int fd)
{
    message_t *message = malloc(sizeof(message_t));
    parsed_message_t parsed;
    ssize_t re = 0;

    memset(&parsed, 0, sizeof(parsed_message_t));
    re = read(fd, &parsed, sizeof(parsed_message_t));
    if (re != sizeof(parsed_message_t))
        return (NULL);
    message->uuid = strdup(parsed.uuid);
    message->sender = NULL;
    message->body = strdup(parsed.body);
    return (message);
}

void relation_message_thread(server_t *server, int fd)
{
    relation_t relation;
    thread_t *thread = NULL;
    uuid_t *message = NULL;

    SLIST_FOREACH(thread, server->data->threads, next) {
        SLIST_FOREACH(message, thread->messages, next) {
            memset(&relation, 0, sizeof(relation_t));
            strcat(relation.first_uuid, thread->uuid);
            strcat(relation.second_uuid, message->uuid);
            write(fd, &relation, sizeof(relation_t));
        }
    }
}

void load_relation_message_thread(server_t *server, int fd)
{
    relation_t *relation = NULL;
    thread_t *thread = NULL;
    message_t *message = NULL;
    uuid_t *uuid = NULL;

    while ((relation = load_relation(fd))) {
        thread = find_thread_by_uuid(server, relation->first_uuid);
        message = find_message_by_uuid(server, relation->second_uuid);
        if (thread && message) {
            uuid = malloc(sizeof(uuid_t));
            uuid->uuid = strdup(message->uuid);
            SLIST_INSERT_HEAD(thread->messages, uuid, next);
        }
        free(relation);
    }
}
