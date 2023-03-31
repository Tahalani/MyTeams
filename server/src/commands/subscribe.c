/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** subscribe.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iso646.h>
#include "commands.h"
#include "logging_server.h"
#include "server.h"

void display_team(user_t *user)
{
    team_t *team = NULL;

    SLIST_FOREACH(team, user->teams, next) {
        printf("Team uuid: %s\n", team->uuid);
    }
    printf("\n");
}

static void join_team(server_t *server, client_t *client, team_t *team)
{
    if (team == NULL)
        send_basic_message(client->fd, "421");
    else if (team not_eq NULL and client->user->teams == NULL) {
        send_basic_message(client->fd, "200");
        client->user->teams = malloc(sizeof(team_t));
        SLIST_INIT(client->user->teams);
        SLIST_INSERT_HEAD(client->user->teams, team, next);
    } else {
        send_basic_message(client->fd, "200");
        SLIST_INSERT_HEAD(client->user->teams, team, next);
    }
}

void subscribe_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');
    team_t *team = NULL;
    team_t *FakeTeam = malloc(sizeof(team_t));

    if (data[1] == NULL || data[2] not_eq NULL) {
        send_basic_message(client->fd, "400");
        free_array(data);
        return;
    }
    FakeTeam->uuid = strdup(data[1]);
    SLIST_INSERT_HEAD(server->data->teams, FakeTeam, next);
    team = find_team_by_uuid(server, data[1]);
    join_team(server, client, team);
    free_array(data);
    display_team(client->user);
}

void unsubscribe_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');
    team_t *team = NULL;

    if (data[1] == NULL || data[2] not_eq NULL) {
        send_basic_message(client->fd, "400");
        free_array(data);
        return;
    }
    team = find_team_by_uuid(server, data[1]);
    if (team == NULL)
        send_basic_message(client->fd, "421");
    else {
        send_basic_message(client->fd, "200");
        SLIST_REMOVE(client->user->teams, team, team_s, next);
    }
    free_array(data);
}
