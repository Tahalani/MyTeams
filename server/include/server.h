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
    #define UNUSED __attribute__((unused))

    #define CRLF "\r\n"

int teams_server(int argc, char **argv);

bool start_server(int port);

client_t *new_client(int fd);
void close_connection(client_t *connection);
void free_connection(client_t *connection);

user_t *new_user(char *username, int fd);
user_t *find_user_by_uuid(server_t *server, char *uuid);
user_t *find_user_by_name(server_t *server, char *name);
team_t *find_team_by_uuid(server_t *server, char *uuid);
team_t *find_user_team(user_t *user, char *uuid);
user_t *find_user_in_team(team_t *team, char *uuid);

void handle_incoming(server_t *server);
void handle_clients(server_t *server, fd_set *set);
void handle_input(server_t *server, client_t *client, char *input);
int refresh_fdsets(server_t *server, fd_set *set);

void send_basic_message(int fd, char *code);
void send_help_message(int fd);

void send_message_packet(int fd, int code);
void send_user_packet(int fd, user_t *user);

void fatal_error(const char *message);
struct sockaddr *generate_address(int port, char *address);
char *generate_uuid(void);
char *get_username_client(server_t *server, client_t *client);
time_t get_time(void);
team_t *find_team_by_uuid(server_t *server, char *uuid);
channel_t *find_channel_by_uuid(server_t *server, char *uuid);
thread_t *find_thread_by_uuid(server_t *server, char *uuid);
channel_t *find_channel_in_specified_team(server_t *server, char *team_uuid, \
    char *channel_uuid);
thread_t *find_thread_in_specified_channel(server_t *server, \
    char *channel_uuid, char *thread_uuid);

char **str_to_word(char const *str, char separator);
size_t array_len(char **array);
void free_array(char **array);

void create_team(server_t *server, client_t *client, char **data);
void create_channel(server_t *server, client_t *client, char **data);
void create_thread(server_t *server, client_t *client, char **data);
void create_reply(server_t *server, client_t *client, char **data);

void list_team(server_t *server, client_t *client);
void list_channel(server_t *server, client_t *client);
void list_thread(server_t *server, client_t *client);
void list_reply(server_t *server, client_t *client);

#endif
