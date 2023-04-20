/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** channel
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "database.h"
#include "types.h"

static channel_t *load_channel(int fd)
{
    channel_t *channel = malloc(sizeof(channel_t));
    parsed_channel_t parsed;
    ssize_t re = 0;

    memset(&parsed, 0, sizeof(parsed_channel_t));
    re = read(fd, &parsed, sizeof(parsed_channel_t));
    if (re != sizeof(parsed_channel_t))
        return NULL;
    channel->name = strdup(parsed.name);
    channel->uuid = strdup(parsed.uuid);
    channel->description = strdup(parsed.description);
    channel->threads = malloc(sizeof(struct thread_l));
    SLIST_INIT(channel->threads);
    return channel;
}

void load_channels(server_t *server)
{
    channel_t *channel = NULL;
    int fd_channel = open(DB_FILE_CHANNELS, O_RDONLY);

    if (fd_channel == -1)
        return;
    channel = load_channel(fd_channel);
    while (channel != NULL) {
        SLIST_INSERT_HEAD(server->data->channels, channel, next);
        channel = load_channel(fd_channel);
    }
    close(fd_channel);
}

static void save_channel(channel_t *channel, int fd)
{
    parsed_channel_t parsed;

    memset(&parsed, 0, sizeof(parsed_channel_t));
    strcat(parsed.name, channel->name);
    strcat(parsed.uuid, channel->uuid);
    strcat(parsed.description, channel->description);
    write(fd, &parsed, sizeof(parsed_channel_t));
}

void save_channels(server_t *server)
{
    int fd = open(DB_FILE_CHANNELS, O_RDWR | O_CREAT, 0777);
    channel_t *channel = NULL;

    if (fd == -1) {
        return;
    }
    SLIST_FOREACH(channel, server->data->channels, next) {
        save_channel(channel, fd);
    }
    close(fd);
}
