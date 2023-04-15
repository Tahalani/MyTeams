/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** team
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

void save_team(team_t *team, int fd)
{
    parsed_team_t parsed;

    memset(&parsed, 0, sizeof(parsed_team_t));
    strcat(parsed.name, team->name);
    strcat(parsed.uuid, team->uuid);
    strcat(parsed.description, team->description);
    write(fd, &parsed, sizeof(parsed_team_t));
}

team_t *load_team(int fd)
{
    team_t *team = malloc(sizeof(team_t));
    parsed_team_t parsed;

    memset(&parsed, 0, sizeof(parsed_team_t));
    ssize_t re = read(fd, &parsed, sizeof(parsed_team_t));
    if (re != sizeof(parsed_team_t))
        return (NULL);
    team->name = strdup(parsed.name);
    team->uuid = strdup(parsed.uuid);
    team->description = strdup(parsed.description);
    team->channels = malloc(sizeof(struct thread_l));
    team->users = malloc(sizeof(struct user_l));
    SLIST_INIT(team->channels);
    SLIST_INIT(team->users);
    return (team);
}
