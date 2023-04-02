/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** team
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"
#include "server.h"

static void add_new_team(server_t *server, char *name, char *description)
{
    team_t *new_team = malloc(sizeof(team_t));

    if (new_team == NULL)
        fatal_error("Malloc failed");
    new_team->uuid = generate_uuid();
    new_team->name = name;
    new_team->description = description;
    new_team->users = malloc(sizeof(struct user_l));
    SLIST_INIT(new_team->users);
    new_team->channels = malloc(sizeof(struct thread_l));
    SLIST_INIT(new_team->channels);
    SLIST_INSERT_HEAD(server->data->teams, new_team, next);
}

void create_team(server_t *server, client_t *client, char **data)
{
    if (data[1] == NULL || data[2] == NULL) {
        send_basic_message(client->fd, "400");
        return;
    }
    add_new_team(server, data[1], data[2]);
    send_basic_message(client->fd, "200");
}

void list_team(server_t *server, client_t *client)
{
    team_t *team = NULL;
    unsigned int nbr_teams = 0;

    SLIST_FOREACH(team, server->data->teams, next)
        nbr_teams++;
    team = NULL;
    if (nbr_teams == 0) {
        send_basic_message(client->fd, "570");
        return;
    }
    dprintf(client->fd, "%d team(s) available%s", nbr_teams, CRLF);
    SLIST_FOREACH(team, server->data->teams, next) {
        dprintf(client->fd, "%s (%s)%s", team->name, team->uuid, CRLF);
    }
    send_basic_message(client->fd, "200");
}
