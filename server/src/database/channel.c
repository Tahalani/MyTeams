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
#include <unistd.h>

#include "server.h"

void save_channel(channel_t *channel, int fd)
{
    parsed_channel_t parsed;

    memset(&parsed, 0, sizeof(parsed_channel_t));
    strcat(parsed.name, channel->name);
    strcat(parsed.uuid, channel->uuid);
    strcat(parsed.description, channel->description);
    write(fd, &parsed, sizeof(parsed_channel_t));
}

channel_t *load_channel(int fd)
{
    channel_t *channel = malloc(sizeof(channel_t));
    parsed_channel_t parsed;

    memset(&parsed, 0, sizeof(parsed_channel_t));
    ssize_t re = read(fd, &parsed, sizeof(parsed_channel_t));
    if (re != sizeof(parsed_channel_t))
        return (NULL);
    channel->name = strdup(parsed.name);
    channel->uuid = strdup(parsed.uuid);
    channel->description = strdup(parsed.description);
    channel->threads = malloc(sizeof(struct thread_l));
    SLIST_INIT(channel->threads);
    return (channel);
}
