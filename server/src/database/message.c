/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** message
*/

#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "database.h"
#include "server.h"
#include "types.h"

static bool link_message(server_t *server, message_t *message)
{
    thread_t *thread = NULL;
    user_t *user = NULL;
    uuid_t *uuid = NULL;

    if (message->is_private) {
        user = find_user_by_uuid(server, message->target);
        return user != NULL;
    }
    thread = find_thread_by_uuid(server, message->target);
    if (thread != NULL) {
        uuid = malloc(sizeof(uuid_t));
        uuid->uuid = strdup(message->uuid);
        SLIST_INSERT_HEAD(thread->messages, uuid, next);
    }
    return thread != NULL;
}

static message_t *load_message(int fd)
{
    message_t *message = malloc(sizeof(message_t));
    parsed_message_t parsed;
    ssize_t re = 0;

    memset(&parsed, 0, sizeof(parsed_message_t));
    re = read(fd, &parsed, sizeof(parsed_message_t));
    if (re != sizeof(parsed_message_t)) {
        free(message);
        return (NULL);
    }
    message->uuid = strdup(parsed.uuid);
    message->body = strdup(parsed.body);
    message->author = strdup(parsed.author);
    message->target = strdup(parsed.target);
    message->created_at = parsed.created_at;
    message->is_private = parsed.is_private;
    return (message);
}

void load_messages(server_t *server)
{
    message_t *message = NULL;
    int fd_message = open(DB_FILE_MESSAGES, O_RDONLY);

    if (fd_message == -1)
        return;
    message = load_message(fd_message);
    while (message != NULL) {
        if (link_message(server, message)) {
            SLIST_INSERT_HEAD(server->data->messages, message, next);
        }
        message = load_message(fd_message);
    }
    close(fd_message);
}

static void save_message(message_t *message, int fd)
{
    parsed_message_t parsed;

    memset(&parsed, 0, sizeof(parsed_message_t));
    strcat(parsed.uuid, message->uuid);
    strcat(parsed.body, message->body);
    strcat(parsed.author, message->author);
    strcat(parsed.target, message->target);
    parsed.created_at = message->created_at;
    parsed.is_private = message->is_private;
    write(fd, &parsed, sizeof(parsed_message_t));
}

void save_messages(server_t *server)
{
    int fd = open(DB_FILE_MESSAGES, O_RDWR | O_CREAT, 0777);
    message_t *message = NULL;

    if (fd == -1) {
        return;
    }
    SLIST_FOREACH(message, server->data->messages, next) {
        save_message(message, fd);
    }
    close(fd);
}
