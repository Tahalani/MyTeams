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

    #include "packets.h"
    #include "types.h"

    #define MAX_CONNECTIONS 50

    #define CRLF "\r\n"

// Core functions
int teams_server(int argc, char **argv);
bool start_server(int port);

bool handle_stdin(void);
void handle_incoming(server_t *server);
void handle_clients(server_t *server, fd_set *set);
void handle_input(server_t *server, client_t *client, command_packet_t *packet);
int refresh_fdsets(server_t *server, fd_set *set);
void clear_buffer(int fd, command_packet_t *packet);

// Packets
void send_message_packet(int fd, int code);
void send_context_packet(int fd, packet_context_t context);
void send_team_packet(int fd, team_t *team, packet_command_t context);
void send_channel_packet(int fd, channel_t *channel, packet_command_t context);
void send_thread_packet(int fd, thread_t *thread, packet_command_t context);
void send_user_packet(int fd, user_t *user, packet_command_t context);
void send_error_packet(int fd, packet_error_t error, char *uuid);

// Objects
client_t *new_client(int fd);
void close_connection(client_t *connection);
void free_connection(client_t *connection);

user_t *new_user(char *username, int fd);
user_t *find_user_by_uuid(server_t *server, char *uuid);
user_t *find_user_by_name(server_t *server, char *name);

team_t *new_team(char *name, char *description);
team_t *find_team_by_uuid(server_t *server, char *uuid);
team_t *find_team_by_name(server_t *server, char *name);

channel_t *new_channel(char *name, char *description, team_t *team);
channel_t *find_channel_by_uuid(server_t *server, char *uuid);
channel_t *find_channel_in_team_by_uuid(server_t *server, team_t *team, \
    char *uuid);
channel_t *find_channel_in_team_by_name(server_t *server, team_t *team, \
    char *name);

thread_t *new_thread(char *title, char *message, channel_t *channel);
thread_t *find_thread_by_uuid(server_t *server, char *uuid);
thread_t *find_thread_in_channel_by_uuid(server_t *server, \
    channel_t *channel, char *uuid);
thread_t *find_thread_in_channel_by_title(server_t *server, \
    channel_t *channel, char *title);

message_t *find_message_by_uuid(server_t *server, char *uuid);

void send_basic_message(int fd, char *code);

// Utils
void fatal_error(const char *message);
struct sockaddr *generate_address(int port, char *address);
char *generate_uuid(void);
char *get_username_client(server_t *server, client_t *client);
time_t get_time(void);

char **str_to_word(char const *str, char separator);
void free_array(char **array);

void create_team(server_t *server, client_t *client, command_packet_t *packet);
void create_channel(server_t *server, client_t *client, \
    command_packet_t *packet);
void create_thread(server_t *server, client_t *client, \
    command_packet_t *packet);
void create_reply(server_t *server, client_t *client, command_packet_t *packet);

void list_team(server_t *server, client_t *client);
void list_channel(server_t *server, client_t *client);
void list_thread(server_t *server, client_t *client);
void list_reply(server_t *server, client_t *client);

void fill_default_use(client_t *client);
void fill_team_use(client_t *client, char **data);
void fill_channel_use(client_t *client, char **data);
void fill_thread_use(client_t *client, char **data);

team_t *get_context_team(server_t *server, use_t *use);
channel_t *get_context_channel(server_t *server, use_t *use);
thread_t *get_context_thread(server_t *server, use_t *use);

#endif
