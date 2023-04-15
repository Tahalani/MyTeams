/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** create
*/

#include <stdio.h>

#include "commands.h"
#include "server.h"
#include "types.h"

void create_command(server_t *server, client_t *client, \
    command_packet_t *packet)
{
    if (client->use->thread_uuid != NULL) {
        create_reply(server, client, packet);
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
    if (client->use->team == NULL) {
        create_team(server, client, packet);
        return;
    }
}

void list_command(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    char *input = "";
    char **data = str_to_word(input, ' ');
    if (data == NULL)
        fatal_error("Malloc failed");
    if (client->use->thread != NULL && data[1] == NULL) {
        list_reply(server, client);
        return;
    }
    if (client->use->channel != NULL && data[1] == NULL) {
        list_thread(server, client);
        return;
    }
    if (client->use->team != NULL && data[1] == NULL) {
        list_channel(server, client);
        return;
    }
    if (client->use->team == NULL && data[1] == NULL) {
        list_team(server, client);
        return;
    }
    send_basic_message(client->fd, "400");
}
