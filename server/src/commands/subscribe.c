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

team_t *copyTeam(team_t *team)
{
    team_t *team_cpy = malloc(sizeof(team_t));

    if (team_cpy == NULL)
        return (NULL);
    team_cpy->uuid = strdup(team->uuid);
    team_cpy->name = NULL;
    team_cpy->description = NULL;
    team_cpy->users = malloc(sizeof(user_t));
    SLIST_INIT(team_cpy->users);
    team_cpy->channels = malloc(sizeof(channel_t));
    SLIST_INIT(team_cpy->channels);
    return (team_cpy);
}

static void join_team(server_t *server, client_t *client, team_t *team)
{
    team_t *team_cpy = NULL;

    if (team == NULL) {
        send_basic_message(client->fd, "421");
        return;
    } else if (team not_eq NULL and client->user->teams == NULL) {
        team_cpy = copyTeam(team);
        client->user->teams = malloc(sizeof(team_t));
        SLIST_INIT(client->user->teams);
        SLIST_INSERT_HEAD(client->user->teams, team_cpy, next);
    } else {
        team_cpy = copyTeam(team);
        SLIST_INSERT_HEAD(client->user->teams, team_cpy, next);
    }
    team->users = malloc(sizeof(user_t));
    SLIST_INIT(team->users);
    SLIST_INSERT_HEAD(team->users, client->user, next);
    send_basic_message(client->fd, "200");
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
    team = find_user_team(client->user, data[1]);
    if (team == NULL)
        send_basic_message(client->fd, "421");
    else {
        send_basic_message(client->fd, "200");
        SLIST_REMOVE(client->user->teams, team, team_s, next);
    }
    free_array(data);
}

void display_team_server(server_t *server)
{
    team_t *team = NULL;
    user_t *user = NULL;

    SLIST_FOREACH(team, server->data->teams, next) {
        printf("Team uuid: %s\n", team->uuid);
    }
}

void subscribed_command(server_t *server, client_t *client, char *input)
{
    team_t *team = NULL;
    user_t *user = NULL;
    char **data = str_to_word(input, ' ');

    if (data[1] == NULL) {
        printf("\n\nteam user:\n");
        SLIST_FOREACH(team, client->user->teams, next) {
            printf("Team uuid: %s\n", team->uuid);
        }
    }
    else {
        team = find_team_by_uuid(server, data[1]);
        printf("\n\n%s user: \n", team->uuid);
        SLIST_FOREACH(user, team->users, next) {
            printf ("%s\n", user->uuid);
        }
    }
    printf("\n\nteam server:\n");
    display_team_server(server);
    send_basic_message(client->fd, "200");
}
