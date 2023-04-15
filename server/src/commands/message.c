/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** reply
*/

#include <stdio.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "constants.h"
#include "logging_server.h"
#include "packets.h"
#include "server.h"
#include "types.h"

static void add_new_message(server_t *server, client_t *client, char *body)
{
    thread_t *thread = get_context_thread(server, client->use);
    message_t *message = NULL;

    if (thread == NULL) {
        send_error_packet(client->fd, ERROR_UNKNOWN_THREAD, \
            client->use->thread_uuid);
        return;
    }
    message = new_message(body, thread, client->user);
    SLIST_INSERT_HEAD(server->data->messages, message, next);
    server_event_reply_created(thread->uuid, client->user->uuid, body);
    send_reply_packet(client->fd, message, COMMAND_CREATE);
}

void create_message(server_t *server, client_t *client, \
    command_packet_t *packet)
{
    ssize_t re = 0;
    char body[MAX_BODY_LENGTH + 1];

    memset(body, 0, MAX_BODY_LENGTH + 1);
    if (packet->data_size != MAX_BODY_LENGTH) {
        send_message_packet(client->fd, 500);
        clear_buffer(client->fd, packet);
        return;
    }
    re = read(client->fd, body, MAX_BODY_LENGTH);
    if (re != MAX_BODY_LENGTH) {
        send_message_packet(client->fd, 500);
    } else {
        add_new_message(server, client, body);
    }
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
            find_message_by_uuid(server, uuid->uuid)->body, \
            find_message_by_uuid(server, uuid->uuid)->sender->username, CRLF);
    }
}

void list_messages(server_t *server, client_t *client)
{
    thread_t *thread = client->use->thread;

    if (thread == NULL) {
        send_basic_message(client->fd, "590");
        return;
    }
    send_list(server, client, thread);
    send_basic_message(client->fd, "200");
}
