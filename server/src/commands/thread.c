/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** thread
*/

#include <stdbool.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "constants.h"
#include "logging_server.h"
#include "packets.h"
#include "server.h"
#include "types.h"

static void send_events(server_t *server, client_t *client, team_t *team, \
    thread_t *thread)
{
    bool sub = false;
    client_t *node = NULL;

    SLIST_FOREACH(node, server->clients, next) {
        sub = is_user_subscribed(node->user, team);
        if (node->user != NULL && (sub || client->user == node->user)) {
            send_thread_packet(node->fd, thread, team, COMMAND_CREATE);
        }
    }
}

static bool check_is_exist(client_t *client)
{
    if (client->use->use_level == 1) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, \
            client->use->team_uuid);
        return false;
    }
    if (client->use->use_level == 2) {
        send_error_packet(client->fd, ERROR_UNKNOWN_CHANNEL, \
            client->use->channel_uuid);
        return false;
    }
    return true;
}

static void add_new_thread(server_t *server, client_t *client, char *title, \
    char *message)
{
    channel_t *channel = get_context_channel(server, client->use);
    team_t *team = get_context_team(server, client->use);
    thread_t *thread = NULL;

    if (check_is_exist(client) == false)
        return;
    thread = find_thread_in_channel_by_title(server, channel, title);
    if (thread != NULL) {
        send_error_packet(client->fd, ERROR_ALREADY_EXIST, NULL);
        return;
    } else if (!is_user_subscribed(client->user, team)) {
        send_error_packet(client->fd, ERROR_UNAUTHORIZED, NULL);
        return;
    }
    thread = new_thread(title, message, client->user, channel);
    SLIST_INSERT_HEAD(server->data->threads, thread, next);
    server_event_thread_created(channel->uuid, thread->uuid, \
        client->user->uuid, title, message);
    send_events(server, client, team, thread);
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
    team_t *team = get_context_team(server, client->use);
    channel_t *channel = get_context_channel(server, client->use);
    uuid_t *uuid = NULL;
    thread_t *thread = NULL;

    if (check_is_exist(client) == false)
        return;
    SLIST_FOREACH(uuid, channel->threads, next) {
        thread = find_thread_in_channel_by_uuid(server, channel, uuid->uuid);
        if (thread != NULL) {
            send_thread_packet(client->fd, thread, team, COMMAND_LIST);
        }
    }
    send_message_packet(client->fd, 200);
}
