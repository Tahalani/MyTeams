/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** saving
*/

#include <unistd.h>
#include <sys/queue.h>
#include <sys/stat.h>

#include "server.h"
#include "types.h"

static void save_message_loop(server_t *server, thread_t *thread)
{
    int fd_message = get_fd_file("MESSAGE");
    uuid_t *uuid_message = NULL;
    message_t *message = NULL;

    SLIST_FOREACH(uuid_message, thread->messages, next) {
        message = find_message_by_uuid(server, uuid_message->uuid);
        save_message(message, fd_message);
    }
    close(fd_message);
}

static void save_thread_loop(server_t *server, channel_t *channel)
{
    int fd_thread = get_fd_file("THREAD");
    uuid_t *uuid_thread = NULL;
    thread_t *thread = NULL;

    SLIST_FOREACH(uuid_thread, channel->threads, next) {
        thread = find_thread_by_uuid(server, uuid_thread->uuid);
        save_thread(thread, fd_thread);
        save_message_loop(server, thread);
    }
    close(fd_thread);
}

static void save_channel_loop(server_t *server, team_t *team)
{
    int fd_channel = get_fd_file("CHANNEL");
    uuid_t *uuid_channel = NULL;
    channel_t *channel = NULL;

    SLIST_FOREACH(uuid_channel, team->channels, next) {
        channel = find_channel_by_uuid(server, uuid_channel->uuid);
        save_channel(channel, fd_channel);
        save_thread_loop(server, channel);
    }
    close(fd_channel);
}

static void save_team_loop(server_t *server)
{
    user_t *user = NULL;
    team_t *team = NULL;
    int fd_user = get_fd_file("USER");
    int fd_team = get_fd_file("TEAM");

    SLIST_FOREACH(user, server->data->users, next)
        save_user(user, fd_user);
    SLIST_FOREACH(team, server->data->teams, next) {
        save_team(team, fd_team);
        save_channel_loop(server, team);
    }
    close(fd_user);
    close(fd_team);
}

void save_data(server_t *server)
{
    mkdir("server/database/", 0777);
    int fd_relation_team_user = get_fd_file("TEAM_USER");
    int fd_relation_channel_team = get_fd_file("CHANNEL_TEAM");
    int fd_relation_thread_channel = get_fd_file("THREAD_CHANNEL");
    int fd_relation_message_thread = get_fd_file("MESSAGE_THREAD");

    save_team_loop(server);
    relation_team_user(server, fd_relation_team_user);
    relation_channel_team(server, fd_relation_channel_team);
    relation_thread_channel(server, fd_relation_thread_channel);
    relation_message_thread(server, fd_relation_message_thread);
    close(fd_relation_team_user);
    close(fd_relation_channel_team);
    close(fd_relation_thread_channel);
    close(fd_relation_message_thread);
}
