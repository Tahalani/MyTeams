/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** reply
*/

#include <stdbool.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "logging_server.h"
#include "packets.h"
#include "server.h"
#include "types.h"

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
    if (client->use->use_level == 3) {
        send_error_packet(client->fd, ERROR_UNKNOWN_THREAD, \
            client->use->thread_uuid);
        return false;
    }
    return true;
}

static void add_new_message(server_t *server, client_t *client, char *body)
{
    team_t *team = get_context_team(server, client->use);
    thread_t *thread = get_context_thread(server, client->use);
    message_t *message = NULL;

    if (check_is_exist(client) == false)
        return;
    message = new_message(body, thread, client->user);
    SLIST_INSERT_HEAD(server->data->messages, message, next);
    server_event_reply_created(thread->uuid, client->user->uuid, body);
    send_reply_packet(client->fd, message, team, COMMAND_CREATE);
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

void list_messages(server_t *server, client_t *client)
{
    team_t *team = get_context_team(server, client->use);
    thread_t *thread = get_context_thread(server, client->use);
    uuid_t *uuid = NULL;
    message_t *message = NULL;

    if (check_is_exist(client) == false)
        return;
    SLIST_FOREACH(uuid, thread->messages, next) {
        message = find_message_in_thread_by_uuid(server, thread, uuid->uuid);
        if (message != NULL) {
            send_reply_packet(client->fd, message, team, COMMAND_LIST);
        }
    }
    send_message_packet(client->fd, 200);
}
