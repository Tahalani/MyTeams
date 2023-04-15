/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** thread
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

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

    memset(&parsed, 0, sizeof(parsed_thread_t));
    ssize_t re = read(fd, &parsed, sizeof(parsed_thread_t));
    if (re != sizeof(parsed_thread_t))
        return (NULL);
    thread->name = strdup(parsed.name);
    thread->uuid = strdup(parsed.uuid);
    thread->message = strdup(parsed.description);
    thread->messages = malloc(sizeof(struct message_l));
    SLIST_INIT(thread->messages);
    return (thread);
}
