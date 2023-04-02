/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** use
*/

#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "server.h"

static bool fill_default_use(client_t *client)
{
    client->use->team = NULL;
    client->use->channel = NULL;
    client->use->thread = NULL;
    return true;
}

static bool fill_team_use(server_t *server, client_t *client, char **data)
{
    team_t *obj = find_team_by_uuid(server, data[1]);

    fill_default_use(client);
    if (obj == NULL) {
        send_basic_message(client->fd, "570");
        return false;
    }
    client->use->team = obj;
    return true;
}

static bool fill_channel_use(server_t *server, client_t *client, char **data)
{
    channel_t *obj = NULL;

    if (!fill_team_use(server, client, data)) {
        return false;
    }
    obj = find_channel_in_specified_team(server, data[1], data[2]);
    if (obj == NULL) {
        send_basic_message(client->fd, "570");
        return false;
    }
    client->use->channel = obj;
    client->use->thread = NULL;
    return true;
}

static bool fill_thread_use(server_t *server, client_t *client, char **data)
{
    thread_t *obj = NULL;

    if (!fill_channel_use(server, client, data)) {
        return false;
    }
    obj = find_thread_in_specified_channel(server, data[2], data[3]);
    if (obj == NULL) {
        send_basic_message(client->fd, "570");
        return false;
    }
    client->use->thread = obj;
    return true;
}

void use_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');
    size_t len = array_len(data);
    bool done = false;

    if (len > 4)
        send_basic_message(client->fd, "400");
    if (len == 1)
        done = fill_default_use(client);
    else if (len == 2)
        done = fill_team_use(server, client, data);
    if (len == 3)
        done = fill_channel_use(server, client, data);
    else if (len == 4)
        done = fill_thread_use(server, client, data);
    if (done)
        send_basic_message(client->fd, "200");
    free_array(data);
}
