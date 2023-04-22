/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** team
*/

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "database.h"
#include "types.h"

static team_t *load_team(int fd)
{
    team_t *team = malloc(sizeof(team_t));
    parsed_team_t parsed;
    ssize_t re = 0;

    memset(&parsed, 0, sizeof(parsed_team_t));
    re = read(fd, &parsed, sizeof(parsed_team_t));
    if (re != sizeof(parsed_team_t)) {
        free(team);
        return (NULL);
    }
    team->name = strdup(parsed.name);
    team->uuid = strdup(parsed.uuid);
    team->description = strdup(parsed.description);
    team->channels = malloc(sizeof(struct thread_l));
    team->users = malloc(sizeof(struct user_l));
    SLIST_INIT(team->channels);
    SLIST_INIT(team->users);
    return (team);
}

void load_teams(server_t *server)
{
    team_t *team = NULL;
    int fd_team = open(DB_FILE_TEAMS, O_RDONLY);

    if (fd_team == -1)
        return;
    team = load_team(fd_team);
    while (team != NULL) {
        SLIST_INSERT_HEAD(server->data->teams, team, next);
        team = load_team(fd_team);
    }
    close(fd_team);
}

static void save_team(team_t *team, int fd)
{
    parsed_team_t parsed;

    memset(&parsed, 0, sizeof(parsed_team_t));
    strcat(parsed.name, team->name);
    strcat(parsed.uuid, team->uuid);
    strcat(parsed.description, team->description);
    write(fd, &parsed, sizeof(parsed_team_t));
}

void save_teams(server_t *server)
{
    int fd = open(DB_FILE_TEAMS, O_RDWR | O_CREAT, 0777);
    team_t *team = NULL;

    if (fd == -1) {
        return;
    }
    SLIST_FOREACH(team, server->data->teams, next) {
        save_team(team, fd);
    }
    close(fd);
}
