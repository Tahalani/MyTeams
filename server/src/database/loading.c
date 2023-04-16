/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** loading
*/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "server.h"
#include "logging_server.h"

static void load_user_loop(server_t *server)
{
    user_t *user = NULL;
    int fd_user = open("server/database/USER", O_RDONLY);

    if (fd_user == -1)
        return;
    user = load_user(fd_user);
    while (user != NULL) {
        SLIST_INSERT_HEAD(server->data->users, user, next);
        server_event_user_loaded(user->uuid, user->username);
        user = load_user(fd_user);
    }
    close(fd_user);
}

static void load_team_channel_loop(server_t *server)
{
    team_t *team = NULL;
    channel_t *channel = NULL;
    int fd_team = open("server/database/TEAM", O_RDONLY);
    int fd_channel = open("server/database/CHANNEL", O_RDONLY);

    if (fd_team == -1 || fd_channel == -1)
        return;
    team = load_team(fd_team);
    channel = load_channel(fd_channel);
    while (team != NULL) {
        SLIST_INSERT_HEAD(server->data->teams, team, next);
        team = load_team(fd_team);
    }
    while (channel != NULL) {
        SLIST_INSERT_HEAD(server->data->channels, channel, next);
        channel = load_channel(fd_channel);
    }
    close(fd_team);
    close(fd_channel);
}

static void load_thread_message_loop(server_t *server)
{
    thread_t *thread = NULL;
    message_t *message = NULL;
    int fd_thread = open("server/database/THREAD", O_RDONLY);
    int fd_message = open("server/database/MESSAGE", O_RDONLY);

    if (fd_thread == -1 || fd_message == -1)
        return;
    thread = load_thread(fd_thread);
    message = load_message(fd_message);
    while (thread != NULL) {
        SLIST_INSERT_HEAD(server->data->threads, thread, next);
        thread = load_thread(fd_thread);
    }
    while (message != NULL) {
        SLIST_INSERT_HEAD(server->data->messages, message, next);
        message = load_message(fd_message);
    }
    close(fd_thread);
    close(fd_message);
}

static void load_relation_loop(server_t *server)
{
    int fd_relation_team_user = open("server/database/TEAM_USER", O_RDONLY);
    int fd_relation_channel_team =
        open("server/database/CHANNEL_TEAM", O_RDONLY);
    int fd_relation_thread_channel =
        open("server/database/THREAD_CHANNEL", O_RDONLY);
    int fd_relation_message_thread =
        open("server/database/MESSAGE_THREAD", O_RDONLY);

    if (fd_relation_team_user == -1 ||
    fd_relation_channel_team == -1 || fd_relation_thread_channel == -1 ||
    fd_relation_message_thread == -1)
        return;
    load_relation_team_user(server, fd_relation_team_user);
    load_relation_channel_team(server, fd_relation_channel_team);
    load_relation_thread_channel(server, fd_relation_thread_channel);
    load_relation_message_thread(server, fd_relation_message_thread);
    close(fd_relation_team_user);
    close(fd_relation_channel_team);
    close(fd_relation_thread_channel);
    close(fd_relation_message_thread);
}

void load_data(server_t *server)
{
    load_user_loop(server);
    load_team_channel_loop(server);
    load_thread_message_loop(server);
    load_relation_loop(server);
}
