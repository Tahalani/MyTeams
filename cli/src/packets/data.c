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
