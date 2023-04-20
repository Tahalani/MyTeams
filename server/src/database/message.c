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
#include <sys/queue.h>
#include <unistd.h>

#include "database.h"
#include "types.h"

// TODO: Link message to target
static void link_message(server_t *server, message_t *message)
{

}

static message_t *load_message(int fd)
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

void load_messages(server_t *server)
{
    message_t *message = NULL;
    int fd_message = open(DB_FILE_MESSAGES, O_RDONLY);

    if (fd_message == -1)
        return;
    message = load_message(fd_message);
    while (message != NULL) {
        SLIST_INSERT_HEAD(server->data->messages, message, next);
        link_message(server, message);
        message = load_message(fd_message);
    }
    close(fd_message);
}

static void save_message(message_t *message, int fd)
{
    parsed_message_t parsed;

    memset(&parsed, 0, sizeof(parsed_message_t));
    strcat(parsed.uuid, message->uuid);
    strcat(parsed.uuid_user, message->sender->uuid);
    strcat(parsed.body, message->body);
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
