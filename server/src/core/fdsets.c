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

static void handle_client(server_t *server, client_t *client)
{
    char *line = NULL;
    size_t size = 0;
    ssize_t r = getline(&line, &size, client->file);
    bool close = r < 0 || r >= BUFFER_SIZE;

    if (r >= BUFFER_SIZE) {
        return;
    }
    if (close) {
        close_connection(client);
        SLIST_REMOVE(server->clients, client, client_s, next);
        free_connection(client);
    } else {
        handle_input(server, client, line);
    }
    free(line);
}

int refresh_fdsets(server_t *server, fd_set *set, int sig_fd)
{
    int max_fd = server->socket_fd;
    client_t *node = NULL;

    FD_ZERO(set);
    FD_SET(server->socket_fd, set);
    FD_SET(sig_fd, set);
    SLIST_FOREACH(node, server->clients, next) {
        FD_SET(node->fd, set);
        max_fd = MAX(max_fd, node->fd);
    }
    return MAX(max_fd, sig_fd);
}

void handle_incoming(server_t *server)
{
    int new_fd = accept(server->socket_fd, NULL, NULL);
    client_t *client = NULL;

    if (new_fd == -1) {
        perror("accept failed");
        return;
    }
    client = new_client(new_fd);
    client->file = fdopen(new_fd, "r");
    if (client->file == NULL) {
        close(new_fd);
        free_connection(client);
        return;
    }
    SLIST_INSERT_HEAD(server->clients, client, next);
    send_basic_message(new_fd, "220");
}

void handle_clients(server_t *server, fd_set *set)
{
    client_t *node = server->clients->slh_first;
    client_t *tmp = NULL;

    while (node != NULL) {
        tmp = node->next.sle_next;
        if (FD_ISSET(node->fd, set)) {
            handle_client(server, node);
        }
        node = tmp;
    }
}
