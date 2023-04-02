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

    printf("\n");
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
        team->users = malloc(sizeof(user_t));
        SLIST_INIT(client->user->teams);
        SLIST_INIT(team->users);
        SLIST_INSERT_HEAD(client->user->teams, team, next);
        SLIST_INSERT_HEAD(team->users, client->user, next);
    } else {
        send_basic_message(client->fd, "200");
        SLIST_INSERT_HEAD(client->user->teams, team, next);
        SLIST_INSERT_HEAD(team->users, client->user, next);
    }
}

void subscribe_command(server_t *server, client_t *client, char *input)
{
    char **data = str_to_word(input, ' ');
    team_t *team = NULL;
    team_t *FakeTeam = malloc(sizeof(team_t));
    user_t *user = NULL;

    if (data[1] == NULL || data[2] not_eq NULL) {
        send_basic_message(client->fd, "400");
        free_array(data);
        return;
    }
    FakeTeam->uuid = strdup(data[1]);
    SLIST_INSERT_HEAD(server->data->teams, FakeTeam, next);
    team = find_team_by_uuid(server, data[1]);
    join_team(server, client, team);

    team_t *team3 = find_team_by_uuid(server, "team2");
    if (team3 == NULL)
        printf("team is null\n");
    else {
        printf("uuid team: %s\n", team3->uuid);
        SLIST_FOREACH(user, team3->users, next) {
            printf ("uuid user: %s ", user->uuid);
        }
    }
    printf("\n\n");
    free_array(data);
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


void subscribed_command(server_t *server, client_t *client, char *input)
{
    team_t *team = NULL;
    user_t *user = NULL;
    char **data = str_to_word(input, ' ');

    if (data[1] == NULL)
        display_team(client->user);
    else {
        team = find_team_by_uuid(server, data[1]);
        printf("team name: %s\n", team->uuid);
        SLIST_FOREACH(user, team->users, next) {
            printf ("uuid user: %s ", user->uuid);
        }
    }
    send_basic_message(client->fd, "200");
}
