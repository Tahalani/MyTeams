/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** data.c
*/

#include <unistd.h>

#include "logging_client.h"
#include "packets.h"
#include "types.h"

void team_packet_handler(client_t *client)
{
    team_packet_t packet;
    ssize_t re = read(client->fd, &packet, sizeof(team_packet_t));

    if (re != sizeof(team_packet_t)) {
        return;
    }
    if (packet.context == COMMAND_CREATE)
        client_event_team_created(packet.uuid, packet.name, packet.description);
    if (packet.context == COMMAND_LIST || packet.context == COMMAND_SUBSCRIBED)
        client_print_teams(packet.uuid, packet.name, packet.description);
    if (packet.context == COMMAND_INFO)
        client_print_team(packet.uuid, packet.name, packet.description);
    else if (packet.context == COMMAND_SUBSCRIBE)
        client_print_subscribed(client->user_uuid, packet.uuid);
    else if (packet.context == COMMAND_UNSUBSCRIBE)
        client_print_unsubscribed(client->user_uuid, packet.uuid);
}

void channel_packet_handler(client_t *client)
{
    channel_packet_t packet;
    ssize_t re = read(client->fd, &packet, sizeof(channel_packet_t));

    if (re != sizeof(channel_packet_t)) {
        return;
    }
    if (packet.context == COMMAND_CREATE) {
        client_event_channel_created(packet.uuid, packet.name, \
            packet.description);
    } else if (packet.context == COMMAND_LIST) {
        client_team_print_channels(packet.uuid, packet.name, \
            packet.description);
    }
    if (packet.context == COMMAND_INFO) {
        client_print_channel(packet.uuid, packet.name, \
            packet.description);
    }
}

void thread_packet_handler(client_t *client)
{
    thread_packet_t packet;
    ssize_t re = read(client->fd, &packet, sizeof(thread_packet_t));

    if (re != sizeof(thread_packet_t)) {
        return;
    }
    if (packet.context == COMMAND_CREATE) {
        client_event_thread_created(packet.uuid, client->user_uuid, \
        packet.created_at,packet.name, packet.message);
    } else if (packet.context == COMMAND_LIST) {
        client_channel_print_threads(packet.uuid, client->user_uuid, \
        packet.created_at, packet.name, packet.message);
    }
    if (packet.context == COMMAND_INFO) {
        client_print_thread(packet.uuid, client->user_uuid, \
        packet.created_at, packet.name, packet.message);
    }
}

void reply_packet_handler(client_t *client)
{
    reply_packet_t packet;
    ssize_t re = read(client->fd, &packet, sizeof(reply_packet_t));

    if (re != sizeof(reply_packet_t))
        return;
    if (packet.context == COMMAND_CREATE) {
        client_event_thread_reply_received(packet.team_uuid, packet.target, \
            packet.author, packet.body);
    } else if (packet.context == COMMAND_LIST) {
        client_thread_print_replies(packet.target, packet.author, \
            packet.created_at, packet.body);
    }
    if (packet.context == COMMAND_SEND) {
        client_event_private_message_received(packet.author, \
            packet.body);
    } else if (packet.context == COMMAND_MESSAGES) {
        client_private_message_print_messages(packet.author, \
            packet.created_at, packet.body);
    }
}
