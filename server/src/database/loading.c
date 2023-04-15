/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** loading
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

void load_data(data_t *data, server_t *server)
{
    int fd_team = open("server/database/Team/TEAM", O_RDONLY);
    int fd_channel = open("server/database/Team/CHANNEL", O_RDONLY);
    int fd_user = open("server/database/Team/USER", O_RDONLY);
    // int fd_thread = open("server/database/Team/THREAD", O_RDONLY);
    // int fd_message = open("server/database/Team/MESSAGE", O_RDONLY);

    if (fd_team == -1 || fd_channel == -1 /*|| fd_thread == -1*/)
        return;
    team_t *team = load_team(fd_team);
    channel_t *channel = load_channel(fd_channel);
    user_t *user = load_user(fd_user);
    // thread_t *thread = load_thread(fd_thread);
    // message_t *message = NULL;
    // uuid_t *uuid_channel = NULL;
    // uuid_t *uuid_thread = NULL;
    while (user != NULL) {
        SLIST_INSERT_HEAD(data->users, user, next);
        user = load_user(fd_user);
    }
    while (team != NULL) {
        SLIST_INSERT_HEAD(data->teams, team, next);
        team = load_team(fd_team);
    }
    while (channel != NULL) {
        SLIST_INSERT_HEAD(data->channels, channel, next);
        channel = load_channel(fd_channel);
    }
    // while (thread != NULL) {
    //     SLIST_INSERT_HEAD(data->threads, thread, next);
    //     thread = load_thread(fd_thread);
    // }
    // while (message != NULL) {
    //     SLIST_INSERT_HEAD(data->messages, message, next);
    //     message = load_message(fd_message);
    // }

    // SLIST_FOREACH(uuid_channel, team->channels, next) {
    //     channel = find_channel_by_uuid(server, uuid_channel->uuid);
    // }
    close(fd_user);
    close(fd_team);
    close(fd_channel);
    // close(fd_thread);
}
