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

static void end_ftp(server_t *server)
{
    client_t *current = *server->clients;

    while (current != NULL) {
        close_connection(current);
        current = current->next;
    }
    free_connections(*ftp->clients);
    free_users(*ftp->users);
    free_ports(*ftp->ports);
}

static void ftp_loop(ftp_t *ftp)
{
    fd_set set;
    int max_fd = 0;
    int current = 0;

    while (1) {
        max_fd = refresh_fdsets(&set, ftp->fd, ftp->clients);
        current = select(max_fd + 1, &set, NULL, NULL, NULL);
        if (current == -1) {
            perror("select failed");
        }
        if (FD_ISSET(ftp->fd, &set)) {
            handle_incoming(ftp->fd, ftp->clients);
        }
        handle_clients(&set, ftp);
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
    connection_t *clients = NULL;
    user_t *users = NULL;
    port_t *ports = NULL;
    ftp_t ftp = { socket_fd, &clients, &users, &ports };

    if (socket_fd == -1) {
        return false;
    }
    srand((unsigned long) &ftp);
    init_default_user(ftp.users, path);
    ftp_loop(&ftp);
    end_ftp(&ftp);
    free(address);
    return true;
}
