/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** clients.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

client_t *new_client(int fd)
{
    client_t *new = malloc(sizeof(client_t));

    if (new == NULL) {
        fatal_error("malloc failed");
    }
    new->fd = fd;
    new->file = NULL;
    new->user = NULL;
    return new;
}

void close_connection(client_t *connection)
{
    close(connection->fd);
}

void free_connection(client_t *connection)
{
    free(connection);
}
