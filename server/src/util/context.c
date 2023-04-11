/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** context.c
*/

#include <stdbool.h>

#include "server.h"
#include "types.h"

bool fill_default_use(client_t *client)
{
    client->use->team = NULL;
    client->use->channel = NULL;
    client->use->thread = NULL;
    return true;
}

bool fill_team_use(server_t *server, client_t *client, char **data)
{
    team_t *obj = find_team_by_uuid(server, data[1]);

    fill_default_use(client);
    if (obj == NULL) {
        send_message_packet(client->fd, 440);
        return false;
    }
    client->use->team = obj;
    return true;
}

bool fill_channel_use(server_t *server, client_t *client, char **data)
{
    channel_t *obj = NULL;

    if (!fill_team_use(server, client, data)) {
        return false;
    }
    obj = find_channel_in_specified_team(server, data[1], data[2]);
    if (obj == NULL) {
        send_message_packet(client->fd, 441);
        return false;
    }
    client->use->channel = obj;
    client->use->thread = NULL;
    return true;
}

bool fill_thread_use(server_t *server, client_t *client, char **data)
{
    thread_t *obj = NULL;

    if (!fill_channel_use(server, client, data)) {
        return false;
    }
    obj = find_thread_in_specified_channel(server, data[2], data[3]);
    if (obj == NULL) {
        send_message_packet(client->fd, 442);
        return false;
    }
    client->use->thread = obj;
    return true;
}
