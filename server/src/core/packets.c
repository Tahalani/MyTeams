/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** packets.c
*/

#include <string.h>
#include <unistd.h>

#include "packets.h"

void send_message_packet(int fd, int code)
{
    packet_header_t opcode = PACKET_MESSAGE;
    message_packet_t packet;

    packet.code = code;
    write(fd, &opcode, sizeof(packet_header_t));
    write(fd, &packet, sizeof(message_packet_t));
}

void send_context_packet(int fd, packet_context_t context)
{
    packet_header_t opcode = PACKET_CONTEXT;
    context_packet_t packet;

    packet.context = context;
    write(fd, &opcode, sizeof(packet_header_t));
    write(fd, &packet, sizeof(context_packet_t));
}

void send_error_packet(int fd, packet_error_t error, char *uuid)
{
    packet_header_t opcode = PACKET_ERROR;
    error_packet_t packet;

    memset(&packet, 0, sizeof(error_packet_t));
    packet.error = error;
    if (uuid != NULL) {
        strcat(packet.uuid, uuid);
    }
    write(fd, &opcode, sizeof(packet_header_t));
    write(fd, &packet, sizeof(error_packet_t));
}
