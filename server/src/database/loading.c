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
#include "logging_server.h"

void load_data(data_t *data, server_t *server)
{
    int fd_user = open("server/database/USER", O_RDONLY);
    int fd_team = open("server/database/TEAM", O_RDONLY);
    int fd_channel = open("server/database/CHANNEL", O_RDONLY);
    int fd_thread = open("server/database/THREAD", O_RDONLY);
    int fd_message = open("server/database/MESSAGE", O_RDONLY);
    int fd_relation_team_user = open("server/database/TEAM_USER", O_RDONLY);
    int fd_relation_channel_team = open("server/database/CHANNEL_TEAM", O_RDONLY);
    int fd_relation_thread_channel = open("server/database/THREAD_CHANNEL", O_RDONLY);
    int fd_relation_message_thread = open("server/database/MESSAGE_THREAD", O_RDONLY);

    if (fd_team == -1 || fd_channel == -1 || fd_user == -1 || fd_thread == -1
    || fd_message == -1 || fd_relation_team_user == -1 ||
    fd_relation_channel_team == -1 || fd_relation_thread_channel == -1 ||
    fd_relation_message_thread == -1)
        return;
    team_t *team = load_team(fd_team);
    channel_t *channel = load_channel(fd_channel);
    user_t *user = load_user(fd_user);
    thread_t *thread = load_thread(fd_thread);
    message_t *message = load_message(fd_message);
    while (user != NULL) {
        SLIST_INSERT_HEAD(data->users, user, next);
        server_event_user_loaded(user->uuid, user->username);
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
    while (thread != NULL) {
        SLIST_INSERT_HEAD(data->threads, thread, next);
        thread = load_thread(fd_thread);
    }
    while (message != NULL) {
        SLIST_INSERT_HEAD(data->messages, message, next);
        message = load_message(fd_message);
    }
    load_relation_team_user(server, fd_relation_team_user);
    load_relation_channel_team(server, fd_relation_channel_team);
    load_relation_thread_channel(server, fd_relation_thread_channel);
    load_relation_message_thread(server, fd_relation_message_thread);
    close(fd_user);
    close(fd_team);
    close(fd_channel);
    close(fd_thread);
    close(fd_message);
    close(fd_relation_team_user);
    close(fd_relation_channel_team);
    close(fd_relation_thread_channel);
    close(fd_relation_message_thread);
}
