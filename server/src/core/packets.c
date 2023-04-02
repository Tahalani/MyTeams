/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** packets.c
*/

#include <string.h>
#include <unistd.h>
#include "packets.h"
#include "types.h"

void send_message_packet(int fd, int code)
{
    packet_header_t opcode = PACKET_MESSAGE;
    message_packet_t packet;

    packet.code = code;
    write(fd, &opcode, sizeof(packet_header_t));
    write(fd, &packet, sizeof(message_packet_t));
}

void send_user_packet(int fd, user_t *user)
{
    packet_header_t opcode = PACKET_USER;
    user_packet_t packet;

    memset(&packet, 0, sizeof(user_packet_t));
    strcat(packet.uuid, user->uuid);
    strcat(packet.username, user->username);
    packet.status = user->fd != -1;
    write(fd, &opcode, sizeof(packet_header_t));
    write(fd, &packet, sizeof(user_packet_t));
}
