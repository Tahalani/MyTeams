/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** server.h
*/

#ifndef CLI_H_
    #define CLI_H_

    #include <stdbool.h>

    #define SUCCESS 0
    #define FAILURE 84

int teams_cli(int argc, char **argv);

bool start_client(char *address, int port);

bool handle_input(int socket_fd);
bool handle_message(int socket_fd);

#endif
