/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** display
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

void save_channel(team_t *team, channel_t *channel, int fd)
{
    parsed_channel_t parsed;

    memset(&parsed, 0, sizeof(parsed_channel_t));
    strcat(parsed.name, channel->name);
    strcat(parsed.uuid, channel->uuid);
    strcat(parsed.uuid_team, team->uuid);
    strcat(parsed.description, channel->description);
    write(fd, &parsed, sizeof(parsed_channel_t));
}

void save_thread(channel_t *channel, thread_t *thread, int fd)
{
    parsed_thread_t parsed;

    memset(&parsed, 0, sizeof(parsed_thread_t));
    strcat(parsed.name, thread->name);
    strcat(parsed.uuid, thread->uuid);
    strcat(parsed.uuid_channel, channel->uuid);
    strcat(parsed.description, thread->message);
    write(fd, &parsed, sizeof(parsed_thread_t));
}

// void save_messages(thread_t *thread, message_t *message, int fd)
// {
//     parsed_message_t parsed;

//     memset(&parsed, 0, sizeof(parsed_message_t));
//     strcat(parsed.name, message->name);
//     strcat(parsed.uuid, message->uuid);
//     strcat(parsed.uuid_thread, thread->uuid);
//     strcat(parsed.description, message->message);
//     write(fd, &parsed, sizeof(parsed_message_t));
// }

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

channel_t *load_channel(int fd)
{
    channel_t *channel = malloc(sizeof(channel_t));
    parsed_channel_t parsed;

    memset(&parsed, 0, sizeof(parsed_channel_t));
    ssize_t re = read(fd, &parsed, sizeof(parsed_channel_t));
    if (re != sizeof(parsed_channel_t))
        return (NULL);
    channel->name = strdup(parsed.name);
    channel->uuid = strdup(parsed.uuid);
    channel->description = strdup(parsed.description);
    channel->threads = malloc(sizeof(struct thread_l));
    SLIST_INIT(channel->threads);
    return (channel);
}

thread_t *load_thread(int fd)
{
    thread_t *thread = malloc(sizeof(thread_t));
    parsed_thread_t parsed;

    memset(&parsed, 0, sizeof(parsed_thread_t));
    ssize_t re = read(fd, &parsed, sizeof(parsed_thread_t));
    if (re != sizeof(parsed_thread_t))
        return (NULL);
    thread->name = strdup(parsed.name);
    thread->uuid = strdup(parsed.uuid);
    thread->message = strdup(parsed.description);
    thread->messages = malloc(sizeof(struct message_l));
    SLIST_INIT(thread->messages);
    return (thread);
}

void load_all_teams(data_t *data, server_t *server)
{
    int fd_team = open("server/database/Team/TEAM", O_RDONLY);
    int fd_channel = open("server/database/Team/CHANNEL", O_RDONLY);
    int fd_thread = open("server/database/Team/THREAD", O_RDONLY);
    // int fd_message = open("server/database/Team/MESSAGE", O_RDONLY);

    if (fd_team == -1 || fd_channel == -1 || fd_thread == -1)
        return;
    team_t *team = load_team(fd_team);
    channel_t *channel = load_channel(fd_channel);
    thread_t *thread = load_thread(fd_thread);
    // message_t *message = NULL;
    uuid_t *uuid_channel = NULL;
    uuid_t *uuid_thread = NULL;
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
    // while (message != NULL) {
    //     SLIST_INSERT_HEAD(data->messages, message, next);
    //     message = load_message(fd_message);
    // }

    SLIST_FOREACH(uuid_channel, team->channels, next) {
        channel = find_channel_by_uuid(server, uuid_channel->uuid);
    }
    close(fd_team);
    close(fd_channel);
    close(fd_thread);
}

void display_all_teams(server_t *server)
{
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;
    message_t *message = NULL;
    uuid_t *uuid_channel = NULL;
    uuid_t *uuid_thread = NULL;
    uuid_t *uuid_message = NULL;
    int fd_team = get_fd_file("TEAM");
    int fd_channel = get_fd_file("CHANNEL");
    int fd_thread = get_fd_file("THREAD");

    SLIST_FOREACH(team, server->data->teams, next) {
        save_team(team, fd_team);
        SLIST_FOREACH(uuid_channel, team->channels, next) {
            channel = find_channel_by_uuid(server, uuid_channel->uuid);
            save_channel(team, channel, fd_channel);
            SLIST_FOREACH(uuid_thread, channel->threads, next) {
                thread = find_thread_by_uuid(server, uuid_thread->uuid);
                save_thread(channel, thread, fd_thread);
            }
        }
    }
    close(fd_team);
    close(fd_channel);
    close(fd_thread);
}
