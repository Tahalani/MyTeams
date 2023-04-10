/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** packets.c
*/

#include <stdio.h>
#include <unistd.h>
#include "cli.h"
#include "logging_client.h"

void message_packet_handler(int socket_fd)
{
    message_packet_t packet;
    ssize_t re = read(socket_fd, &packet, sizeof(message_packet_t));

    if (re != sizeof(message_packet_t)) {
        return;
    }
    send_rfc_message(packet.code);
}

void user_packet_handler(int socket_fd)
{
    user_packet_t packet;
    ssize_t re = read(socket_fd, &packet, sizeof(user_packet_t));

    if (re != sizeof(user_packet_t)) {
        return;
    }
    client_event_logged_in(packet.uuid, packet.username);
}
