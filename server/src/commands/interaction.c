/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** create
*/

#include <stdio.h>

#include "commands.h"
#include "constants.h"
#include "packets.h"
#include "server.h"
#include "types.h"

void create_command(server_t *server, client_t *client, \
    command_packet_t *packet)
{
    if (client->use->thread_uuid != NULL) {
        create_message(server, client, packet);
        return;
    }
    if (client->use->channel_uuid != NULL) {
        create_thread(server, client, packet);
        return;
    }
    if (client->use->team_uuid != NULL) {
        create_channel(server, client, packet);
        return;
    }
    create_team(server, client, packet);
}

void list_command(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    if (client->use->thread_uuid != NULL) {
        list_messages(server, client);
        return;
    }
    if (client->use->channel_uuid != NULL) {
        list_threads(server, client);
        return;
    }
    if (client->use->team_uuid != NULL) {
        list_channels(server, client);
        return;
    }
    list_teams(server, client);
}
