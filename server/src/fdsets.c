/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** fdsets.c
*/

#include <stdio.h>
#include <sys/socket.h>
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
        // remove connection
        free_connection(client);
    } else {
        //handle_input(ftp, client, line);
    }
}

int refresh_fdsets(server_t *server, fd_set *set)
{
    int max_fd = server->socket_fd;
    client_list_t *node = NULL;

    FD_ZERO(set);
    FD_SET(server->socket_fd, set);
    SLIST_FOREACH(node, server->clients, next) {
        FD_SET(node->item->fd, set);
        max_fd = MAX(max_fd, node->item->fd);
    }
    return max_fd;
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
    //add_connection(list, connection);
    //send_basic_message(new_fd, "220");
}

void handle_clients(server_t *server, fd_set *set)
{
    client_list_t *node = NULL;

    SLIST_FOREACH(node, server->clients, next) {
        if (FD_ISSET(node->item->fd, set)) {
            handle_client(server, node->item);
        }
    }
}
