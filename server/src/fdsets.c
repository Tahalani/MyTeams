/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** fdsets.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>
#include "server.h"

static void handle_client(ftp_t *ftp, connection_t *client)
{
    char *line = NULL;
    size_t size = 0;
    ssize_t r = getline(&line, &size, client->stream);
    bool close = r < 0 || r >= BUFFER_SIZE;

    if (r >= BUFFER_SIZE) {
        return;
    }
    if (close) {
        close_connection(client);
        remove_connection(ftp->clients, client);
    } else {
        handle_input(ftp, client, line);
    }
}

int refresh_fdsets(fd_set *set, int socket_fd, client_t **list)
{
    connection_t *current = *list;
    int max_fd = socket_fd;

    FD_ZERO(set);
    FD_SET(socket_fd, set);
    while (current != NULL) {
        FD_SET(current->fd, set);
        max_fd = MAX(max_fd, current->fd);
        current = current->next;
    }
    return max_fd;
}

void handle_incoming(int socket_fd, connection_t **list)
{
    int new_fd = accept(socket_fd, NULL, NULL);
    connection_t *connection = NULL;

    if (new_fd == -1) {
        perror("accept failed");
        return;
    }
    connection = new_connection(new_fd);
    connection->stream = fdopen(new_fd, "r");
    if (connection->stream == NULL) {
        close(new_fd);
        free_connection(connection);
        return;
    }
    add_connection(list, connection);
    send_basic_message(new_fd, "220");
}

void handle_clients(fd_set *set, ftp_t *ftp)
{
    connection_t *current = *ftp->clients;
    connection_t *tmp = NULL;

    while (current != NULL) {
        tmp = current->next;
        if (FD_ISSET(current->fd, set)) {
            handle_client(ftp, current);
        }
        current = tmp;
    }
}
