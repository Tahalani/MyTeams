/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** users.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cli.h"
#include "logging_client.h"
#include "packets.h"
#include "types.h"

static void update_user(client_t *client, user_packet_t *packet, bool login)
{
    if (client->user_name != NULL) {
        free(client->user_name);
        client->user_name = NULL;
    }
    if (client->user_uuid != NULL) {
        free(client->user_uuid);
        client->user_uuid = NULL;
    }
    if (login) {
        client->user_uuid = strdup(packet->uuid);
        client->user_name = strdup(packet->username);
    }
}

static void handle_login_logout(client_t *client, user_packet_t *packet)
{
    if (packet->context == COMMAND_LOGIN) {
        client_event_logged_in(packet->uuid, packet->username);
        if (packet->status) {
            update_user(client, packet, true);
        }
    } else {
        client_event_logged_out(packet->uuid, packet->username);
        if (packet->status) {
            update_user(client, packet, false);
            client->context = CONTEXT_NONE;
        }
    }
}

void user_packet_handler(client_t *client)
{
    user_packet_t packet;
    ssize_t re = read(client->fd, &packet, sizeof(user_packet_t));

    if (re != sizeof(user_packet_t))
        return;
    if (packet.context == COMMAND_LOGIN || packet.context == COMMAND_LOGOUT)
        handle_login_logout(client, &packet);
    if (packet.context == COMMAND_USER || packet.context == COMMAND_INFO)
        client_print_user(packet.uuid, packet.username, packet.status);
    if (packet.context == COMMAND_USERS || packet.context == COMMAND_SUBSCRIBED)
        client_print_users(packet.uuid, packet.username, packet.status);
}

void context_packet_handler(client_t *client)
{
    context_packet_t packet;
    ssize_t re = read(client->fd, &packet, sizeof(context_packet_t));

    if (re != sizeof(context_packet_t)) {
        return;
    }
    client->context = packet.context;
}

void message_packet_handler(client_t *client)
{
    message_packet_t packet;
    ssize_t re = read(client->fd, &packet, sizeof(message_packet_t));

    if (re != sizeof(message_packet_t)) {
        return;
    }
    send_rfc_message(packet.code);
}
