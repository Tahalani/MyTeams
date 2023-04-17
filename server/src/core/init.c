/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** init.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server.h"

bool setup_server(int socket_fd, struct sockaddr *addr)
{
    int res = bind(socket_fd, addr, sizeof(*addr));

    if (res == -1) {
        perror("bind failed");
        close(socket_fd);
        return false;
    }
    res = listen(socket_fd, MAX_CONNECTIONS);
    if (res == -1) {
        perror("listen failed");
        close(socket_fd);
        return false;
    }
    return true;
}

int init_socket(int port)
{
    struct sockaddr *address = generate_address(port, NULL);
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) {
        perror("socket failed");
        return -1;
    }
    if (!setup_server(socket_fd, address)) {
        return -1;
    }

    return socket_fd;
}
