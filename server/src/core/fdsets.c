/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** fdsets.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/queue.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include "packets.h"
#include "server.h"
#include "types.h"

static void handle_client(server_t *server, client_t *client)
{
    command_packet_t packet;
    ssize_t re = read(client->fd, &packet, sizeof(command_packet_t));

    if (re == 0) {
        close_connection(client);
        SLIST_REMOVE(server->clients, client, client_s, next);
        free_connection(client);
    } else if (re != sizeof(command_packet_t)) {
        send_message_packet(client->fd, 500);
    } else {
        handle_input(server, client, &packet);
    }
}

int refresh_fdsets(server_t *server, fd_set *set)
{
    int max_fd = server->socket_fd;
    client_t *node = NULL;

    FD_ZERO(set);
    FD_SET(0, set);
    FD_SET(server->socket_fd, set);
    SLIST_FOREACH(node, server->clients, next) {
        FD_SET(node->fd, set);
        max_fd = MAX(max_fd, node->fd);
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
    SLIST_INSERT_HEAD(server->clients, client, next);
    send_message_packet(new_fd, 220);
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

bool handle_stdin(void)
{
    bool exit = false;
    size_t len = 0;
    char *line = NULL;

    if (getline(&line, &len, stdin) == -1) {
        exit = true;
    }
    free(line);
    return exit;
}
