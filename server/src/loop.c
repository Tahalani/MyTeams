/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** socket.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

static void end_server(server_t *server)
{
    client_t *current = NULL;

    SLIST_FOREACH(current, server->clients, next) {
        close_connection(current);
    }
}

static void server_loop(server_t *server)
{
    fd_set set;
    int max_fd = 0;
    int current = 0;

    while (1) {
        max_fd = refresh_fdsets(server, &set);
        current = select(max_fd + 1, &set, NULL, NULL, NULL);
        if (current == -1) {
            perror("select failed");
        }
        if (FD_ISSET(server->socket_fd, &set)) {
            handle_incoming(server);
        }
        handle_clients(server, &set);
    }
}

static int init_ftp(struct sockaddr *addr)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int res = 0;

    if (socket_fd == -1) {
        perror("socket failed");
        return -1;
    }
    res = bind(socket_fd, addr, sizeof(*addr));
    if (res == -1) {
        perror("bind failed");
        close(socket_fd);
        return -1;
    }
    res = listen(socket_fd, MAX_CONNECTIONS);
    if (res == -1) {
        perror("listen failed");
        close(socket_fd);
        return -1;
    }
    return socket_fd;
}

bool start_server(int port)
{
    struct sockaddr *address = generate_address(port, NULL);
    int socket_fd = init_ftp(address);
    data_t data;
    struct client_list clients;
    SLIST_INIT(&clients);
    server_t server = { socket_fd, &data, &clients };

    if (socket_fd == -1) {
        return false;
    }
    srand((unsigned long) &server);
    // init data
    server_loop(&server);
    end_server(&server);
    free(address);
    return true;
}
