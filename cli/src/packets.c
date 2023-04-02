/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** packets.c
*/

#include <stdio.h>
#include <unistd.h>
#include "logging_client.h"
#include "messages.h"
#include "packets.h"

void message_packet_handler(int socket_fd)
{
    message_packet_t packet;
    ssize_t re = read(socket_fd, &packet, sizeof(message_packet_t));

    if (re != sizeof(message_packet_t)) {
        return;
    }
    for (size_t i = 0; i < MESSAGES_COUNT; i++) {
        if (MESSAGES[i].code == packet.code) {
            printf("%s\n", MESSAGES[i].message);
            return;
        }
    }
    fprintf(stderr, "Unknown RFC message code: %d\n", packet.code);
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
