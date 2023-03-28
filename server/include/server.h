/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stdbool.h>
    #include <sys/socket.h>
    #include "types.h"

    #define SUCCESS 0
    #define FAILURE 84
    #define BUFFER_SIZE 1024
    #define MAX_CONNECTIONS 50

int teams_server(int argc, char **argv);

bool start_server(int port);

client_t *new_client(int fd);
void close_connection(client_t *connection);
void free_connection(client_t *connection);

void handle_incoming(server_t *server);
void handle_clients(server_t *server, fd_set *set);
int refresh_fdsets(server_t *server, fd_set *set);

void fatal_error(const char *message);
struct sockaddr *generate_address(int port, char *address);

#endif
