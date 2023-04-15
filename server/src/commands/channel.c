/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** channel
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

static void add_new_channel(server_t *server, client_t *client, \
    char *name, char *description)
{
    team_t *team = get_context_team(server, client->use);
    channel_t *channel = NULL;

    if (team == NULL) {
        send_error_packet(client->fd, ERROR_UNKNOWN_TEAM, \
            client->use->team_uuid);
        return;
    }
    channel = find_channel_in_team_by_name(server, team, name);
    if (channel != NULL) {
        send_error_packet(client->fd, ERROR_ALREADY_EXIST, NULL);
        return;
    }
    channel = new_channel(name, description, team);
    SLIST_INSERT_HEAD(server->data->channels, channel, next);
    server_event_channel_created(team->uuid, channel->uuid, channel->name);
    send_channel_packet(client->fd, channel, COMMAND_CREATE);
}

void create_channel(server_t *server, client_t *client, \
    UNUSED command_packet_t *packet)
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
        add_new_channel(server, client, name, description);
    }
}

static void send_list(server_t *server, client_t *client, team_t *team)
{
    uuid_t *uuid = NULL;
    unsigned int nbr_channel = 0;

    SLIST_FOREACH(uuid, team->channels, next)
        nbr_channel++;
    uuid = NULL;
    if (nbr_channel == 0) {
        send_basic_message(client->fd, "580");
        return;
    }
    dprintf(client->fd, "%d channel(s) available%s", nbr_channel, CRLF);
    SLIST_FOREACH(uuid, team->channels, next) {
        dprintf(client->fd, "%s (%s)%s", \
        find_channel_by_uuid(server, uuid->uuid)->name, uuid->uuid, CRLF);
    }
}

void list_channel(server_t *server, client_t *client)
{
    team_t *team = client->use->team;

    if (team == NULL) {
        send_basic_message(client->fd, "570");
        return;
    }
    send_list(server, client, team);
    send_basic_message(client->fd, "200");
}
