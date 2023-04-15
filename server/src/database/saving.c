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

void relation_team_user(server_t *server, int fd)
{
    relation_t relation;
    user_t *user = NULL;
    uuid_t *team = NULL;

    SLIST_FOREACH(user, server->data->users, next) {
        SLIST_FOREACH(team, user->teams, next) {
            memset(&relation, 0, sizeof(relation_t));
            strcat(relation.first_uuid, user->uuid);
            strcat(relation.second_uuid, team->uuid);
            write(fd, &relation, sizeof(relation_t));
        }
    }
}

void relation_channel_team(server_t *server, int fd)
{
    relation_t relation;
    team_t *team = NULL;
    uuid_t *channel = NULL;

    SLIST_FOREACH(team, server->data->teams, next) {
        SLIST_FOREACH(channel, team->channels, next) {
            memset(&relation, 0, sizeof(relation_t));
            strcat(relation.first_uuid, team->uuid);
            strcat(relation.second_uuid, channel->uuid);
            write(fd, &relation, sizeof(relation_t));
        }
    }
}

void relation_thread_channel(server_t *server, int fd)
{
    relation_t relation;
    channel_t *channel = NULL;
    uuid_t *thread = NULL;

    SLIST_FOREACH(channel, server->data->channels, next) {
        SLIST_FOREACH(thread, channel->threads, next) {
            memset(&relation, 0, sizeof(relation_t));
            strcat(relation.first_uuid, channel->uuid);
            strcat(relation.second_uuid, thread->uuid);
            write(fd, &relation, sizeof(relation_t));
        }
    }
}

// void relation_message_thread(server_t *server, int fd)
// {
//     relation_t relation;
//     thread_t *thread = NULL;
//     uuid_t *message = NULL;

//     SLIST_FOREACH(thread, server->data->threads, next) {
//         SLIST_FOREACH(message, thread->messages, next) {
//             memset(&relation, 0, sizeof(relation_t));
//             strcat(relation.first_uuid, thread->uuid);
//             strcat(relation.second_uuid, message->uuid);
//             write(fd, &relation, sizeof(relation_t));
//         }
//     }
// }

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
    int fd_relation_team_user = get_fd_file("TEAM_USER");
    int fd_relation_channel_team = get_fd_file("CHANNEL_TEAM");
    int fd_relation_thread_channel = get_fd_file("THREAD_CHANNEL");
    // int fd_relation_message_thread = get_fd_file("MESSAGE_THREAD");

    SLIST_FOREACH(user, server->data->users, next)
        save_user(user, fd_user);
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
    relation_team_user(server, fd_relation_team_user);
    relation_channel_team(server, fd_relation_channel_team);
    relation_thread_channel(server, fd_relation_thread_channel);
    close(fd_user);
    close(fd_team);
    close(fd_channel);
    close(fd_thread);
    close(fd_relation_team_user);
    close(fd_relation_channel_team);
    close(fd_relation_thread_channel);
    // close(fd_relation_message_thread);
}
