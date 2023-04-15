/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** clients.c
*/

#include <stdlib.h>
#include <unistd.h>

#include "server.h"
#include "types.h"

client_t *new_client(int fd)
{
    client_t *new = malloc(sizeof(client_t));
    use_t *use = malloc(sizeof(use_t));

    if (new == NULL || use == NULL) {
        fatal_error("malloc failed");
    }
    new->fd = fd;
    new->file = NULL;
    new->user = NULL;
    new->use = use;
    new->use->team = NULL;
    new->use->team_uuid = NULL;
    new->use->channel = NULL;
    new->use->channel_uuid = NULL;
    new->use->thread = NULL;
    new->use->thread_uuid = NULL;
    return new;
}

void close_connection(client_t *client)
{
    if (client->user != NULL)
        client->user->fd = -1;
    close(client->fd);
}

void free_connection(client_t *client)
{
    free(client->use);
    free(client);
}
