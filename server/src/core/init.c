/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** init.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server.h"

bool setup_server(int socket_fd, struct sockaddr *addr)
{
    int res = bind(socket_fd, addr, sizeof(*addr));

    if (res == -1) {
        printf("bind failed\n");
        close(socket_fd);
        return false;
    }
    res = listen(socket_fd, MAX_CONNECTIONS);
    if (res == -1) {
        printf("listen failed\n");
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
        printf("socket failed\n");
        return -1;
    }
    if (!setup_server(socket_fd, address)) {
        return -1;
    }
    free(address);
    return socket_fd;
}
