/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** info
*/

#include <stdio.h>
#include <sys/queue.h>

#include "commands.h"
#include "server.h"
#include "types.h"

static void display_user(server_t *server, user_t *user, int fd)
{
    uuid_t *uuid = NULL;
    team_t *team = NULL;

    dprintf(user->fd, "%s (%s)%s", user->username,
    user->uuid, CRLF);
    SLIST_FOREACH(uuid, user->teams, next) {
        team = find_team_by_uuid(server, uuid->uuid);
        dprintf (fd, "%s (%s) %s%s",
        team->name, uuid->uuid, team->description, CRLF);
    }
}

static void display_team(server_t *server, team_t *team, client_t *client)
{
    uuid_t *uuid = NULL;
    channel_t *channel = NULL;

    dprintf(client->user->fd, "%s (%s) %s%s",
    team->name, team->uuid, team->description, CRLF);
    SLIST_FOREACH(uuid, team->users, next)
        dprintf(client->user->fd, "%s (%s)%s",
        find_user_by_uuid(server, uuid->uuid)->username, uuid->uuid, CRLF);
    SLIST_FOREACH(uuid, team->channels, next) {
        channel = find_channel_by_uuid(server, uuid->uuid);
        dprintf(client->user->fd, "%s (%s) %s%s",
        channel->name, uuid->uuid, channel->description, CRLF);
    }
}

static void display_channel(server_t *server, channel_t *channel, \
client_t *client)
{
    uuid_t *uuid = NULL;
    thread_t *thread = NULL;

    dprintf(client->fd, "%s (%s) %s%s",
    channel->name, channel->uuid, channel->description, CRLF);
    SLIST_FOREACH(uuid, channel->threads, next) {
        thread = find_thread_by_uuid(server, uuid->uuid);
        dprintf(client->fd, "%s (%s) %s%s",
        thread->name, uuid->uuid, thread->message, CRLF);
    }
}

static void display_thread(server_t *server, thread_t *thread, \
client_t *client)
{
    uuid_t *uuid = NULL;
    message_t *msg = NULL;

    dprintf(client->fd, "%s (%s) %s%s",
    thread->name, thread->uuid, thread->message, CRLF);
    SLIST_FOREACH(uuid, thread->messages, next) {
        msg = find_message_by_uuid(server, uuid->uuid);
        dprintf(client->fd, "%s (%s)", msg->uuid, msg->content);
        dprintf(client->fd, " %ld%s", msg->time, CRLF);
        display_user(server, msg->sender, client->fd);
    }
}

void info_command(UNUSED server_t *server, client_t *client, \
UNUSED char *input)
{
    if (client->user == NULL) {
        send_basic_message(client->fd, "530");
        return;
    }
    if (client->use->team == NULL && client->use->channel == NULL
    && client->use->thread == NULL)
        display_user(server, client->user, client->fd);
    else if (client->use->team != NULL && client->use->channel == NULL
    && client->use->thread == NULL)
        display_team(server, client->use->team, client);
    if (client->use->channel != NULL && client->use->team != NULL
    && client->use->thread == NULL)
        display_channel(server, client->use->channel, client);
    else if (client->use->thread != NULL && client->use->channel != NULL
    && client->use->team != NULL)
        display_thread(server, client->use->thread, client);
    send_basic_message(client->fd, "200");
}
