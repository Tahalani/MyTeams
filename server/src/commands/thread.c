/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** thread
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

static void add_new_thread(server_t *server, client_t *client, char *title, \
    char *message)
{
    channel_t *channel = get_context_channel(server, client->use);
    thread_t *thread = NULL;

    if (client->use->not_found == 1) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, \
            client->use->channel_uuid);
        return;
    }
    if (client->use->not_found == 2) {
        send_error_packet(client->fd, ERROR_UNKNOWN_CHANNEL, \
            client->use->channel_uuid);
        return;
    }
    thread = find_thread_in_channel_by_title(server, channel, title);
    if (thread != NULL) {
        send_error_packet(client->fd, ERROR_ALREADY_EXIST, NULL);
        return;
    }
    thread = new_thread(title, message, channel);
    SLIST_INSERT_HEAD(server->data->threads, thread, next);
    server_event_thread_created(channel->uuid, thread->uuid, \
        client->user->uuid, title, message);
    send_thread_packet(client->fd, thread, COMMAND_CREATE);
}

void create_thread(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    size_t size = MAX_NAME_LENGTH + MAX_BODY_LENGTH;
    ssize_t re = 0;
    ssize_t re2 = 0;
    char name[MAX_NAME_LENGTH + 1];
    char body[MAX_BODY_LENGTH + 1];

    memset(name, 0, MAX_NAME_LENGTH + 1);
    memset(body, 0, MAX_BODY_LENGTH + 1);
    if (packet->data_size != size) {
        send_message_packet(client->fd, 500);
        clear_buffer(client->fd, packet);
        return;
    }
    re = read(client->fd, name, MAX_NAME_LENGTH);
    re2 = read(client->fd, body, MAX_BODY_LENGTH);
    if (re != MAX_NAME_LENGTH || re2 != MAX_BODY_LENGTH) {
        send_message_packet(client->fd, 500);
    } else {
        add_new_thread(server, client, name, body);
    }
}

void list_threads(server_t *server, client_t *client)
{
    channel_t *channel = get_context_channel(server, client->use);
    uuid_t *uuid = NULL;
    thread_t *thread = NULL;

    if (client->use->not_found == 1) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, \
            client->use->channel_uuid);
        return;
    }
    if (client->use->not_found == 2) {
        send_error_packet(client->fd, ERROR_UNKNOWN_CHANNEL, \
            client->use->channel_uuid);
        return;
    }
    SLIST_FOREACH(uuid, channel->threads, next) {
        thread = find_thread_in_channel_by_uuid(server, channel, uuid->uuid);
        if (thread != NULL) {
            send_thread_packet(client->fd, thread, COMMAND_LIST);
        }
    }
    send_message_packet(client->fd, 200);
}
