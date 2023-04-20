/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** client.c
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include "cli.h"
#include "packets.h"
#include "types.h"

static int refresh_fdsets(int socket_fd, fd_set *set)
{
    int max_fd = 0;

    FD_ZERO(set);
    FD_SET(socket_fd, set);
    FD_SET(0, set);
    max_fd = MAX(socket_fd, 0);
    return max_fd;
}

static void client_loop(client_t *client)
{
    fd_set set;
    bool exit = false;
    int max_fd = 0;

    while (!exit) {
        max_fd = refresh_fdsets(client->fd, &set);
        if (select(max_fd + 1, &set, NULL, NULL, NULL) == -1) {
            printf("select failed\n");
            return;
        }
        if (FD_ISSET(0, &set)) {
            exit = handle_input(client);
        }
        if (FD_ISSET(client->fd, &set)) {
            exit = handle_packet(client);
        }
    }
}

static int init_client(struct sockaddr *addr)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int res = 0;

    if (socket_fd == -1) {
        printf("socket failed\n");
        return -1;
    }
    res = connect(socket_fd, addr, sizeof(*addr));
    if (res == -1) {
        printf("connect failed\n");
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
    client_t client = { 0, NULL, NULL, CONTEXT_NONE };

    client.fd = init_client(addr_ptr);
    if (client.fd == -1) {
        return false;
    }
    client_loop(&client);
    close(client.fd);
    free(client.user_uuid);
    free(client.user_name);
    return true;
}
