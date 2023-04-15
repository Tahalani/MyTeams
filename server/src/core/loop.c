/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** socket.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/queue.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>

#include "server.h"
#include "types.h"

static void end_server(server_t *server)
{
    client_t *current = NULL;

    SLIST_FOREACH(current, server->clients, next) {
        close_connection(current);
    }
    free(server->data->teams);
    free(server->data->channels);
    free(server->data->threads);
    free(server->data->messages);
    free(server->data->users);
}

static void server_loop(server_t *server)
{
    fd_set set;
    int max_fd = 0;
    int current = 0;
    bool exit = false;

    while (!exit) {
        max_fd = refresh_fdsets(server, &set);
        current = select(max_fd + 1, &set, NULL, NULL, NULL);
        if (current == -1) {
            perror("select failed");
        }
        if (FD_ISSET(0, &set)) {
            exit = handle_stdin();
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

void init_data(data_t *data)
{
    data->users = malloc(sizeof(struct user_list));
    data->teams = malloc(sizeof(struct team_list));
    data->channels = malloc(sizeof(struct channel_list));
    data->threads = malloc(sizeof(struct thread_list));
    data->messages = malloc(sizeof(struct message_list));
    if (data->users == NULL || data->teams == NULL || data->channels == NULL
    || data->threads == NULL || data->messages == NULL)
        fatal_error("malloc failed");
    SLIST_INIT(data->users);
    SLIST_INIT(data->teams);
    SLIST_INIT(data->channels);
    SLIST_INIT(data->threads);
    SLIST_INIT(data->messages);
}

bool start_server(int port)
{
    struct sockaddr *address = generate_address(port, NULL);
    int socket_fd = init_ftp(address);
    data_t *data = calloc(sizeof(data_t), 1);
    struct client_list clients;
    SLIST_INIT(&clients);
    server_t server = { socket_fd, data, &clients};
    setsockopt(port, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    if (socket_fd == -1 || data == NULL) {
        return false;
    }
    srand((unsigned long) &server + time(NULL));
    init_data(data);
    server_loop(&server);
    end_server(&server);
    free(address);
    free(data);
    return true;
}
