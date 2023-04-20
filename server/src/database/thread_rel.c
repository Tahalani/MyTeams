/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** thread_rel.c
*/

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "database.h"
#include "server.h"
#include "types.h"

static void load_thread_relations(server_t *server, int fd)
{
    relation_t *relation = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;
    uuid_t *uuid = NULL;

    while ((relation = load_relation(fd))) {
        channel = find_channel_by_uuid(server, relation->first_uuid);
        thread = find_thread_by_uuid(server, relation->second_uuid);
        if (channel != NULL && thread != NULL) {
            uuid = malloc(sizeof(uuid_t));
            ensure_allocated(uuid);
            uuid->uuid = strdup(thread->uuid);
            SLIST_INSERT_HEAD(channel->threads, uuid, next);
        }
        free(relation);
    }
}

void load_channel_thread_relations(server_t *server)
{
    int fd = open(DB_FILE_REL_CHANNELS_THREADS, O_RDONLY);

    if (fd == -1) {
        return;
    }
    load_thread_relations(server, fd);
    close(fd);
}

void save_thread_relations(server_t *server, int fd)
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

void save_channel_thread_relations(server_t *server)
{
    int fd = open(DB_FILE_REL_CHANNELS_THREADS, O_RDWR | O_CREAT, 0777);

    if (fd == -1) {
        return;
    }
    save_thread_relations(server, fd);
    close(fd);
}
