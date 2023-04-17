/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** loading
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "database.h"
#include "server.h"

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
    load_users(server);
    load_teams(server);
    load_channels(server);
    load_threads(server);
    load_messages(server);
    load_relation_loop(server);
}
