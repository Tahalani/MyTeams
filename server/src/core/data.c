/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** data.c
*/

#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "packets.h"
#include "server.h"
#include "types.h"

void send_team_packet(int fd, team_t *team, user_t *user, \
    packet_command_t context)
{
    packet_header_t opcode = PACKET_TEAM;
    team_packet_t packet;

    memset(&packet, 0, sizeof(team_packet_t));
    strcat(packet.uuid, team->uuid);
    strcat(packet.name, team->name);
    strcat(packet.description, team->description);
    if (user != NULL) {
        strcat(packet.author, user->uuid);
    }
    packet.context = context;
    write(fd, &opcode, sizeof(packet_header_t));
    write(fd, &packet, sizeof(team_packet_t));
}

void send_channel_packet(int fd, channel_t *channel, user_t *user, \
    packet_command_t context)
{
    packet_header_t opcode = PACKET_CHANNEL;
    channel_packet_t packet;

    memset(&packet, 0, sizeof(channel_packet_t));
    strcat(packet.uuid, channel->uuid);
    strcat(packet.name, channel->name);
    strcat(packet.description, channel->description);
    if (user != NULL) {
        strcat(packet.author, user->uuid);
    }
    packet.context = context;
    write(fd, &opcode, sizeof(packet_header_t));
    write(fd, &packet, sizeof(channel_packet_t));
}

void send_thread_packet(int fd, thread_t *thread, team_t *team, \
    packet_command_t context)
{
    packet_header_t opcode = PACKET_THREAD;
    thread_packet_t packet;

    memset(&packet, 0, sizeof(thread_packet_t));
    strcat(packet.uuid, thread->uuid);
    strcat(packet.name, thread->name);
    strcat(packet.message, thread->message);
    strcat(packet.author, thread->author);
    strcat(packet.team_uuid, team->uuid);
    packet.created_at = thread->created_at;
    packet.context = context;
    write(fd, &opcode, sizeof(packet_header_t));
    write(fd, &packet, sizeof(thread_packet_t));
}

void send_reply_packet(int fd, message_t *message, team_t *team, \
    packet_command_t context)
{
    packet_header_t opcode = PACKET_REPLY;
    reply_packet_t packet;

    memset(&packet, 0, sizeof(reply_packet_t));
    strcat(packet.body, message->body);
    strcat(packet.author, message->author);
    strcat(packet.target, message->target);
    if (team != NULL)
        strcat(packet.team_uuid, team->uuid);
    packet.created_at = message->created_at;
    packet.context = context;
    write(fd, &opcode, sizeof(packet_header_t));
    write(fd, &packet, sizeof(reply_packet_t));
}

void send_user_packet(int fd, user_t *user, bool online, \
    packet_command_t context)
{
    packet_header_t opcode = PACKET_USER;
    user_packet_t packet;

    memset(&packet, 0, sizeof(user_packet_t));
    strcat(packet.uuid, user->uuid);
    strcat(packet.username, user->username);
    packet.status = online;
    packet.context = context;
    write(fd, &opcode, sizeof(packet_header_t));
    write(fd, &packet, sizeof(user_packet_t));
}
