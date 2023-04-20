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
#include <sys/queue.h>
#include <unistd.h>

#include "database.h"
#include "types.h"

static thread_t *load_thread(int fd)
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
    thread->author = strdup(parsed.author);
    thread->messages = malloc(sizeof(struct message_l));
    SLIST_INIT(thread->messages);
    return (thread);
}

void load_threads(server_t *server)
{
    thread_t *thread = NULL;
    int fd_thread = open(DB_FILE_THREADS, O_RDONLY);

    if (fd_thread == -1)
        return;
    thread = load_thread(fd_thread);
    while (thread != NULL) {
        SLIST_INSERT_HEAD(server->data->threads, thread, next);
        thread = load_thread(fd_thread);
    }
    close(fd_thread);
}

static void save_thread(thread_t *thread, int fd)
{
    parsed_thread_t parsed;

    memset(&parsed, 0, sizeof(parsed_thread_t));
    strcat(parsed.name, thread->name);
    strcat(parsed.uuid, thread->uuid);
    strcat(parsed.description, thread->message);
    strcat(parsed.author, thread->author);
    write(fd, &parsed, sizeof(parsed_thread_t));
}

void save_threads(server_t *server)
{
    int fd = open(DB_FILE_THREADS, O_RDWR | O_CREAT, 0777);
    thread_t *thread = NULL;

    if (fd == -1) {
        return;
    }
    SLIST_FOREACH(thread, server->data->threads, next) {
        save_thread(thread, fd);
    }
    close(fd);
}
