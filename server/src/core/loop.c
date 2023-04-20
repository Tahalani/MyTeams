/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** socket.c
*/

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <sys/select.h>
#include <sys/signalfd.h>
#include <time.h>

#include "server.h"
#include "types.h"

static void end_server(server_t *server)
{
    client_t *current = NULL;

    SLIST_FOREACH(current, server->clients, next) {
        close_connection(current);
    }
}

static int init_signalfd(void)
{
    int sig_fd = 0;
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sig_fd = signalfd(-1, &mask, 0);
    if (sig_fd == -1)
        fatal_error("signalfd failed");
    sigprocmask(SIG_BLOCK, &mask, NULL);
    return sig_fd;
}

static void server_loop(server_t *server)
{
    fd_set set;
    int max_fd = 0;
    int current = 0;
    bool exit = false;
    int sig_fd = init_signalfd();

    while (!exit) {
        max_fd = refresh_fdsets(server, &set, sig_fd);
        current = select(max_fd + 1, &set, NULL, NULL, NULL);
        if (current == -1)
            fatal_error("select failed");
        if (FD_ISSET(0, &set))
            exit = handle_stdin();
        if (FD_ISSET(sig_fd, &set))
            exit = true;
        if (FD_ISSET(server->socket_fd, &set))
            handle_incoming(server);
        handle_clients(server, &set);
    }
}

static bool init_server(server_t *server, int port)
{
    int socket_fd = init_socket(port);

    if (socket_fd == -1)
        return false;
    server->socket_fd = socket_fd;
    srand((unsigned long) &server + time(NULL));
    load_data(server);
    server_loop(server);
    save_data(server);
    end_server(server);
    return true;
}

bool start_server(int port)
{
    struct user_list users;
    struct client_list clients;
    struct team_list teams;
    struct channel_list channels;
    struct thread_list threads;
    struct message_list messages;
    data_t data = { &users, &teams, &channels, &threads, &messages };
    server_t server = { 0, &data, &clients};

    SLIST_INIT(&clients);
    SLIST_INIT(&users);
    SLIST_INIT(&teams);
    SLIST_INIT(&channels);
    SLIST_INIT(&threads);
    SLIST_INIT(&messages);
    return init_server(&server, port);
}
