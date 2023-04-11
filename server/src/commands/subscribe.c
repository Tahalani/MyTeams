/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** subscribe.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "commands.h"
#include "server.h"
#include "types.h"

static void join_team(client_t *client, team_t *team)
{
    uuid_t *uuid = malloc(sizeof(uuid_t));
    uuid_t *uuid2 = malloc(sizeof(uuid_t));

    if (team == NULL || uuid == NULL || uuid2 == NULL) {
        send_basic_message(client->fd, "421");
        return;
    }
    uuid->uuid = team->uuid;
    SLIST_INSERT_HEAD(client->user->teams, uuid, next);
    uuid2->uuid = client->user->uuid;
    SLIST_INSERT_HEAD(team->users, uuid2, next);
    send_basic_message(client->fd, "200");
}

void subscribe_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');
    team_t *team = NULL;

    if (data[1] == NULL || data[2] != NULL) {
        send_basic_message(client->fd, "400");
        free_array(data);
        return;
    }
    team = find_team_by_uuid(server, data[1]);
    join_team(client, team);
    free_array(data);
}

static void leave_team(client_t *client, team_t *userTeam, uuid_t *uuid)
{
    SLIST_FOREACH(uuid, userTeam->users, next) {
        if (strcmp(uuid->uuid, client->user->uuid) == 0)
            SLIST_REMOVE(userTeam->users, uuid, uuid_s, next);
    }
}

void unsubscribe_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');
    team_t *userTeam = NULL;
    uuid_t *uuid = NULL;

    if (data[1] == NULL || data[2] != NULL) {
        send_basic_message(client->fd, "400");
        free_array(data);
        return;
    }
    SLIST_FOREACH(uuid, client->user->teams, next) {
        if (strcmp(uuid->uuid, data[1]) == 0)
            SLIST_REMOVE(client->user->teams, uuid, uuid_s, next);
    }
    uuid = NULL;
    SLIST_FOREACH(userTeam, server->data->teams, next) {
        if (strcmp(userTeam->uuid, data[1]) == 0)
            leave_team(client, userTeam, uuid);
    }
    send_basic_message(client->fd, "200");
    free_array(data);
}

void subscribed_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');
    team_t *team = NULL;
    uuid_t *uuid = NULL;

    if (data[1] == NULL) {
        SLIST_FOREACH(uuid, client->user->teams, next)
            dprintf (client->fd, "%s (%s)%s",
            find_team_by_uuid(server, uuid->uuid)->name, uuid->uuid, CRLF);
    } else {
        team = find_team_by_uuid(server, data[1]);
        SLIST_FOREACH(uuid, team->users, next)
            dprintf(client->fd, "%s (%s)%s",
            find_user_by_uuid(server, uuid->uuid)->username, uuid->uuid, CRLF);
    }
    send_basic_message(client->fd, "200");
}
