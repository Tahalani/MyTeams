/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** team
*/

#include <stdio.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "constants.h"
#include "logging_server.h"
#include "packets.h"
#include "server.h"
#include "types.h"

static void add_new_team(server_t *server, client_t *client, \
    char *name, char *description)
{
    team_t *team = find_team_by_name(server, name);

    if (team != NULL) {
        send_error_packet(client->fd, ERROR_ALREADY_EXIST, NULL);
        return;
    }
    team = new_team(name, description);
    SLIST_INSERT_HEAD(server->data->teams, team, next);
    server_event_team_created(team->uuid, team->name, client->user->uuid);
    send_team_packet(client->fd, team, COMMAND_CREATE);
}

void create_team(server_t *server, client_t *client, command_packet_t *packet)
{
    size_t size = MAX_NAME_LENGTH + MAX_DESCRIPTION_LENGTH;
    ssize_t re = 0;
    ssize_t re2 = 0;
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];

    memset(name, 0, MAX_NAME_LENGTH + 1);
    memset(description, 0, MAX_DESCRIPTION_LENGTH + 1);
    if (packet->data_size != size) {
        send_message_packet(client->fd, 500);
        clear_buffer(client->fd, packet);
        return;
    }
    re = read(client->fd, name, MAX_NAME_LENGTH);
    re2 = read(client->fd, description, MAX_DESCRIPTION_LENGTH);
    if (re != MAX_NAME_LENGTH || re2 != MAX_DESCRIPTION_LENGTH) {
        send_message_packet(client->fd, 500);
    } else {
        add_new_team(server, client, name, description);
    }
}

void list_teams(server_t *server, client_t *client)
{
    team_t *team = NULL;

    SLIST_FOREACH(team, server->data->teams, next) {
        send_team_packet(client->fd, team, COMMAND_LIST);
    }
    send_message_packet(client->fd, 200);
}
