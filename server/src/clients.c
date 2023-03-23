/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** clients.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "server.h"

client_t *new_connection(int fd)
{
    client_t *new = malloc(sizeof(connection_t));

    if (new == NULL) {
        fatal_error("malloc failed");
    }
    new->fd = fd;
    new->stream = NULL;
    new->data = new_data();
    new->state = USERNAME;
    new->user = NULL;
    new->work_dir = strdup("/");
    new->next = NULL;
    return new;
}

void close_connection(client_t *connection)
{
    close(connection->fd);
}

void free_connection(client_t *connection)
{
    free(connection->data);
    free(connection);
}
