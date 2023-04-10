/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** reply
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"
#include "server.h"

static void add_new_reply(server_t *server, client_t *client, char *message)
{
    uuid_t *uuid = malloc(sizeof(uuid_t));
    message_t *new_reply = malloc(sizeof(message_t));

    if (uuid == NULL || new_reply == NULL)
        fatal_error("Malloc failed");
    new_reply->uuid = generate_uuid();
    new_reply->content = strdup(&message[8]);
    new_reply->time = get_time();
    new_reply->sender = client->user;
    SLIST_INSERT_HEAD(server->data->messages, new_reply, next);
    uuid->uuid = strdup(new_reply->uuid);
    SLIST_INSERT_HEAD(client->use->thread->messages, uuid, next);
}

void create_reply(server_t *server, client_t *client, char *comment)
{
    thread_t *thread = client->use->thread;

    if (comment == NULL) {
        send_basic_message(client->fd, "400");
        return;
    }
    if (thread == NULL) {
        send_basic_message(client->fd, "590");
        return;
    }
    add_new_reply(server, client, comment);
    send_basic_message(client->fd, "200");
}

message_t *find_message_by_uuid(server_t *server, char *uuid)
{
    message_t *message = NULL;

    SLIST_FOREACH(message, server->data->messages, next) {
        if (strcmp(message->uuid, uuid) == 0)
            return message;
    }
    return NULL;
}

static void send_list(server_t *server, client_t *client, thread_t *thread)
{
    uuid_t *uuid = NULL;
    unsigned int nbr_reply = 0;

    SLIST_FOREACH(uuid, thread->messages, next)
        nbr_reply++;
    uuid = NULL;
    if (nbr_reply == 0) {
        send_basic_message(client->fd, "580");
        return;
    }
    dprintf(client->fd, "%d channel(s) available%s", nbr_reply, CRLF);
    SLIST_FOREACH(uuid, thread->messages, next) {
        dprintf(client->fd, "%s (%s)%s", \
            find_message_by_uuid(server, uuid->uuid)->content, \
            find_message_by_uuid(server, uuid->uuid)->sender->username, CRLF);
    }
}

void list_reply(server_t *server, client_t *client)
{
    thread_t *thread = client->use->thread;

    if (thread == NULL) {
        send_basic_message(client->fd, "590");
        return;
    }
    send_list(server, client, thread);
    send_basic_message(client->fd, "200");
}
