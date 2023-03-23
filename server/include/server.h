/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stdbool.h>
    #include "types.h"

    #define SUCCESS 0
    #define FAILURE 84
    #define BUFFER_SIZE 1024
    #define MAX_CONNECTIONS 50

int teams_server(int argc, char **argv);

bool start_server(int port);

client_t *new_client(int fd);

#endif
