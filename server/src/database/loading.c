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

relation_t *load_relation(int fd)
{
    relation_t *relation = malloc(sizeof(relation_t));

    memset(relation, 0, sizeof(relation_t));
    ssize_t re = read(fd, relation, sizeof(relation_t));
    if (re != sizeof(relation_t)) {
        free(relation);
        return NULL;
    }
    return relation;
}

void load_relation_team_user(server_t *server, int fd)
{
    relation_t *relation = NULL;

    while ((relation = load_relation(fd))) {
        user_t *user = find_user_by_uuid(server, relation->first_uuid);
        team_t *team = find_team_by_uuid(server, relation->second_uuid);
        if (user && team) {
            uuid_t *uuid = malloc(sizeof(uuid_t));
            strcpy(uuid->uuid, team->uuid);
            SLIST_INSERT_HEAD(user->teams, uuid, next);
            uuid = malloc(sizeof(uuid_t));
            strcpy(uuid->uuid, user->uuid);
            SLIST_INSERT_HEAD(team->users, uuid, next);
        }
        free(relation);
    }
}

void load_relation_channel_team(server_t *server, int fd)
{
    relation_t *relation = NULL;

    while ((relation = load_relation(fd))) {
        team_t *team = find_team_by_uuid(server, relation->first_uuid);
        channel_t *channel = find_channel_by_uuid(server, relation->second_uuid);
        if (team && channel) {
            uuid_t *uuid = malloc(sizeof(uuid_t));
            strcpy(uuid->uuid, channel->uuid);
            SLIST_INSERT_HEAD(team->channels, uuid, next);
        }
        free(relation);
    }
}

void load_relation_thread_channel(server_t *server, int fd)
{
    relation_t *relation = NULL;

    while ((relation = load_relation(fd))) {
        channel_t *channel = find_channel_by_uuid(server, relation->first_uuid);
        thread_t *thread = find_thread_by_uuid(server, relation->second_uuid);
        if (channel && thread) {
            uuid_t *uuid = malloc(sizeof(uuid_t));
            strcpy(uuid->uuid, thread->uuid);
            SLIST_INSERT_HEAD(channel->threads, uuid, next);
        }
        free(relation);
    }
}

// void load_relation_message_thread(server_t *server, int fd)
// {
//     relation_t *relation = NULL;

//     while ((relation = load_relation(fd))) {
//         thread_t *thread = find_thread_by_uuid(server->data->threads, relation->first_uuid);
//         message_t *message = find_message_by_uuid(server->data->messages, relation->second_uuid);
//         if (thread && message) {
//             uuid_t *uuid = malloc(sizeof(uuid_t));
//             strcpy(uuid->uuid, message->uuid);
//             SLIST_INSERT_HEAD(thread->messages, uuid, next);
//             uuid = malloc(sizeof(uuid_t));
//             strcpy(uuid->uuid, thread->uuid);
//             SLIST_INSERT_HEAD(message->threads, uuid, next);
//         }
//         free(relation);
//     }
// }

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
    load_relation_team_user(server, fd_user);
    load_relation_channel_team(server, fd_team);
    load_relation_thread_channel(server, fd_channel);
    // load_relation_message_thread(server, fd_thread);
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
