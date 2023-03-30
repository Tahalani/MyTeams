/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** client.c
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <sys/param.h>
#include <unistd.h>
#include "cli.h"

static int refresh_fdsets(int socket_fd, fd_set *set)
{
    int max_fd = 0;

    FD_ZERO(set);
    FD_SET(socket_fd, set);
    FD_SET(0, set);
    max_fd = MAX(socket_fd, 0);
    return max_fd;
}

static void client_loop(int socket_fd)
{
    fd_set set;
    bool exit = false;
    int max_fd = 0;

    while (!exit) {
        max_fd = refresh_fdsets(socket_fd, &set);
        if (select(max_fd + 1, &set, NULL, NULL, NULL) == -1) {
            perror("select failed");
            return;
        }
        if (FD_ISSET(0, &set)) {
            handle_input(socket_fd);
        }
        if (FD_ISSET(socket_fd, &set)) {
            exit = handle_message(socket_fd);
        }
    }
}

static int init_client(struct sockaddr *addr)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int res = 0;

    if (socket_fd == -1) {
        perror("socket failed");
        return -1;
    }
    res = connect(socket_fd, addr, sizeof(*addr));
    if (res == -1) {
        perror("connect failed");
        return -1;
    }
    return socket_fd;
}

bool start_client(char *address, int port)
{
    struct sockaddr_in addr = {
            .sin_family = AF_INET,
            .sin_port = htons(port),
            .sin_addr = { inet_addr(address) },
    };
    struct sockaddr *addr_ptr = (struct sockaddr *)&addr;
    int socket_fd = 0;

    socket_fd = init_client(addr_ptr);
    if (socket_fd == -1) {
        return false;
    }
    client_loop(socket_fd);
    close(socket_fd);
    return true;
}
