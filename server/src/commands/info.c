/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** info
*/

#include <stdbool.h>
#include <stdio.h>

#include "commands.h"
#include "constants.h"
#include "packets.h"
#include "server.h"
#include "types.h"

static void display_team(client_t *client)
{
    if (client->use->use_level == 1) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, \
            client->use->team_uuid);
        return;
    }
    send_team_packet(client->fd, client->use->team, NULL, COMMAND_INFO);
}

static void display_channel(client_t *client)
{
    if (client->use->use_level == 1) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, \
            client->use->team_uuid);
        return;
    }
    if (client->use->use_level == 2) {
        send_error_packet(client->fd, ERROR_UNKNOWN_CHANNEL, \
            client->use->channel_uuid);
        return;
    }
    send_channel_packet(client->fd, client->use->channel, NULL, COMMAND_INFO);
}

static void display_thread(server_t *server, client_t *client)
{
    team_t *team = get_context_team(server, client->use);

    if (client->use->use_level == 1) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, \
            client->use->team_uuid);
        return;
    }
    if (client->use->use_level == 2) {
        send_error_packet(client->fd, ERROR_UNKNOWN_CHANNEL, \
            client->use->channel_uuid);
        return;
    }
    if (client->use->use_level == 3) {
        send_error_packet(client->fd, ERROR_UNKNOWN_THREAD, \
            client->use->thread_uuid);
        return;
    }
    send_thread_packet(client->fd, client->use->thread, team, COMMAND_INFO);
}

void info_command(UNUSED server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
{
    if (client->use->team_uuid == NULL) {
        send_user_packet(client->fd, client->user, true, COMMAND_INFO);
        return;
    }
    if (client->use->channel_uuid == NULL) {
        display_team(client);
        return;
    }
    if (client->use->thread_uuid == NULL) {
        display_channel(client);
        return;
    }
    display_thread(server, client);
}
