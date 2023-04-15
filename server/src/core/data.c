/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** data.c
*/

#include <string.h>
#include <unistd.h>

#include "packets.h"
#include "types.h"

void send_team_packet(int fd, team_t *team, packet_command_t context)
{
    packet_header_t opcode = PACKET_TEAM;
    team_packet_t packet;

    memset(&packet, 0, sizeof(team_packet_t));
    strcat(packet.uuid, team->uuid);
    strcat(packet.name, team->name);
    strcat(packet.description, team->description);
    packet.context = context;
    write(fd, &opcode, sizeof(packet_header_t));
    write(fd, &packet, sizeof(team_packet_t));
}

void send_user_packet(int fd, user_t *user, packet_command_t context)
{
    packet_header_t opcode = PACKET_USER;
    user_packet_t packet;

    memset(&packet, 0, sizeof(user_packet_t));
    strcat(packet.uuid, user->uuid);
    strcat(packet.username, user->username);
    packet.status = user->fd != -1;
    packet.context = context;
    write(fd, &opcode, sizeof(packet_header_t));
    write(fd, &packet, sizeof(user_packet_t));
}
