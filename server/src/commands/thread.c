/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** thread
*/

#include <stdio.h>
#include <stdlib.h>
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

    if (channel == NULL) {
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

channel_t *find_channel_in_specified_team(server_t *server, char *team_uuid, \
    char *channel_uuid)
{
    team_t *team = NULL;
    uuid_t *uuid = NULL;

    team = find_team_by_uuid(server, team_uuid);
    if (team == NULL)
        return NULL;
    SLIST_FOREACH(uuid, team->channels, next) {
        if (strcmp(uuid->uuid, channel_uuid) == 0)
            return find_channel_by_uuid(server, channel_uuid);
    }
    return NULL;
}

void list_thread(server_t *server, client_t *client)
{
    uuid_t *uuid = NULL;
    unsigned int nbr_thread = 0;
    channel_t *channel = find_channel_in_specified_team(server,
        client->use->team->uuid, client->use->channel->uuid);

    if (channel == NULL) {
        send_basic_message(client->fd, "580");
        return;
    }
    SLIST_FOREACH(uuid, channel->threads, next)
        nbr_thread++;
    uuid = NULL;
    dprintf(client->fd, "%d thread(s) available%s", nbr_thread, CRLF);
    SLIST_FOREACH(uuid, channel->threads, next) {
        dprintf(client->fd, "%s (%s)%s", \
            find_thread_by_uuid(server, uuid->uuid)->name, uuid->uuid, CRLF);
    }
}
