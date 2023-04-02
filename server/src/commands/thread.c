/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** thread
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"
#include "server.h"

static void add_new_thread(server_t *server, client_t *client, char *title, \
    char *message)
{
    uuid_t *uuid = malloc(sizeof(uuid_t));
    channel_t *channel_node =
        find_channel_by_uuid(server, client->use->channel->uuid);
    thread_t *new_thread = malloc(sizeof(thread_t));

    if (new_thread == NULL)
        fatal_error("Malloc failed");
    new_thread->uuid = generate_uuid();
    new_thread->name = strdup(title);
    new_thread->message = strdup(message);
    new_thread->messages = malloc(sizeof(struct message_l));
    SLIST_INIT(new_thread->messages);
    new_thread->messages = NULL;
    uuid->uuid = strdup(new_thread->uuid);
    SLIST_INSERT_HEAD(server->data->threads, new_thread, next);
    SLIST_INSERT_HEAD(channel_node->threads, uuid, next);
}

void create_thread(server_t *server, client_t *client, char **data)
{
    team_t *team = NULL;
    channel_t *channel = NULL;

    if (data[1] == NULL || data[2] == NULL) {
        send_basic_message(client->fd, "400");
        return;
    }
    team = find_team_by_uuid(server, client->use->team->uuid);
    if (team == NULL) {
        send_basic_message(client->fd, "570");
        return;
    }
    channel = find_channel_by_uuid(server, client->use->channel->uuid);
    if (channel == NULL) {
        send_basic_message(client->fd, "580");
        return;
    }
    add_new_thread(server, client, data[1], data[2]);
    send_basic_message(client->fd, "200");
}

channel_t *find_channel_in_specified_team(server_t *server, char *team_uuid, \
    char *channel_uuid)
{
    team_t *team = NULL;
    uuid_t *uuid = NULL;

    team = find_team_by_uuid(server, team_uuid);
    if (team == NULL)
        return NULL;
    SLIST_FOREACH(uuid, team->channels, next) {
        if (strcmp(uuid->uuid, channel_uuid) == 0)
            return find_channel_by_uuid(server, channel_uuid);
    }
    return NULL;
}

thread_t *find_thread_in_specified_channel(server_t *server, \
    char *channel_uuid, char *thread_uuid)
{
    channel_t *channel = NULL;
    uuid_t *uuid = NULL;

    channel = find_channel_by_uuid(server, channel_uuid);
    if (channel == NULL)
        return NULL;
    SLIST_FOREACH(uuid, channel->threads, next) {
        if (strcmp(uuid->uuid, thread_uuid) == 0)
            return find_thread_by_uuid(server, thread_uuid);
    }
    return NULL;
}

void list_thread(server_t *server, client_t *client)
{
    uuid_t *uuid = NULL;
    unsigned int nbr_thread = 0;
    channel_t *channel = find_channel_in_specified_team(server,
        client->use->team->uuid, client->use->channel->uuid);

    if (channel == NULL) {
        send_basic_message(client->fd, "580");
        return;
    }
    SLIST_FOREACH(uuid, channel->threads, next)
        nbr_thread++;
    uuid = NULL;
    dprintf(client->fd, "%d thread(s) available%s", nbr_thread, CRLF);
    SLIST_FOREACH(uuid, channel->threads, next) {
        dprintf(client->fd, "%s (%s)%s", \
            find_thread_by_uuid(server, uuid->uuid)->name, uuid->uuid, CRLF);
    }
}
