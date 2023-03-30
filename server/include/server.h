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
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512
    #define UNUSED __attribute__((unused))

    #define CRLF "\r\n"

int teams_server(int argc, char **argv);

bool start_server(int port);

client_t *new_client(int fd);
void close_connection(client_t *connection);
void free_connection(client_t *connection);

user_t *new_user(char *username);
user_t *find_user_by_uuid(server_t *server, char *uuid);
user_t *find_user_by_name(server_t *server, char *name);

void handle_incoming(server_t *server);
void handle_clients(server_t *server, fd_set *set);
void handle_input(server_t *server, client_t *client, char *input);
int refresh_fdsets(server_t *server, fd_set *set);

void send_basic_message(int fd, char *code);
void send_help_message(int fd);

void fatal_error(const char *message);
struct sockaddr *generate_address(int port, char *address);
char *generate_uuid(void);
char *get_username_client(server_t *server, client_t *client);
time_t get_time(void);

char **str_to_word(char const *str, char separator);
void free_array(char **array);

#endif
