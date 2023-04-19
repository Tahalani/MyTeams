/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** thread
*/

#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "server.h"
#include "types.h"

void save_thread(thread_t *thread, int fd)
{
    parsed_thread_t parsed;

    memset(&parsed, 0, sizeof(parsed_thread_t));
    strcat(parsed.name, thread->name);
    strcat(parsed.uuid, thread->uuid);
    strcat(parsed.description, thread->message);
    write(fd, &parsed, sizeof(parsed_thread_t));
}

thread_t *load_thread(int fd)
{
    thread_t *thread = malloc(sizeof(thread_t));
    parsed_thread_t parsed;
    ssize_t re = 0;

    memset(&parsed, 0, sizeof(parsed_thread_t));
    re = read(fd, &parsed, sizeof(parsed_thread_t));
    if (re != sizeof(parsed_thread_t))
        return (NULL);
    thread->name = strdup(parsed.name);
    thread->uuid = strdup(parsed.uuid);
    thread->message = strdup(parsed.description);
    thread->messages = malloc(sizeof(struct message_l));
    SLIST_INIT(thread->messages);
    return (thread);
}

void relation_thread_channel(server_t *server, int fd)
{
    relation_t relation;
    channel_t *channel = NULL;
    uuid_t *thread = NULL;

    SLIST_FOREACH(channel, server->data->channels, next) {
        SLIST_FOREACH(thread, channel->threads, next) {
            memset(&relation, 0, sizeof(relation_t));
            strcat(relation.first_uuid, channel->uuid);
            strcat(relation.second_uuid, thread->uuid);
            write(fd, &relation, sizeof(relation_t));
        }
    }
}

void load_relation_thread_channel(server_t *server, int fd)
{
    relation_t *relation = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;
    uuid_t *uuid = NULL;

    while ((relation = load_relation(fd))) {
        channel = find_channel_by_uuid(server, relation->first_uuid);
        thread = find_thread_by_uuid(server, relation->second_uuid);
        if (channel && thread) {
            uuid = malloc(sizeof(uuid_t));
            uuid->uuid = strdup(thread->uuid);
            SLIST_INSERT_HEAD(channel->threads, uuid, next);
        }
        free(relation);
    }
}
