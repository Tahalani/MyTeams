/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** saving
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

void save_data(server_t *server)
{
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;
    user_t *user = NULL;
    // message_t *message = NULL;
    uuid_t *uuid_channel = NULL;
    uuid_t *uuid_thread = NULL;
    // uuid_t *uuid_message = NULL;
    int fd_user = get_fd_file("USER");
    int fd_team = get_fd_file("TEAM");
    int fd_channel = get_fd_file("CHANNEL");
    int fd_thread = get_fd_file("THREAD");

    SLIST_FOREACH(user, server->data->users, next) {
        save_user(user, fd_user);
    }
    SLIST_FOREACH(team, server->data->teams, next) {
        save_team(team, fd_team);
        SLIST_FOREACH(uuid_channel, team->channels, next) {
            channel = find_channel_by_uuid(server, uuid_channel->uuid);
            save_channel(channel, fd_channel);
            SLIST_FOREACH(uuid_thread, channel->threads, next) {
                thread = find_thread_by_uuid(server, uuid_thread->uuid);
                save_thread(thread, fd_thread);
            }
        }
    }
    close(fd_user);
    close(fd_team);
    close(fd_channel);
    close(fd_thread);
}
