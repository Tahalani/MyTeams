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
    if (packet.context == COMMAND_CREATE) {
        client_event_team_created(packet.uuid, packet.name, packet.description);
    }
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
    }
}

void reply_packet_handler(client_t *client)
{
    reply_packet_t packet;
    ssize_t re = read(client->fd, &packet, sizeof(reply_packet_t));

    if (re != sizeof(reply_packet_t)) {
        return;
    }
    if (packet.context == COMMAND_CREATE) {
        client_event_thread_reply_received("", "", client->user_uuid, \
            packet.body);
    }
}
