/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** command.h
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #define COMMANDS_COUNT (sizeof(COMMANDS) / sizeof(command_t))

    #include <stdbool.h>
    #include "packets.h"
    #include "types.h"

typedef void (*command_func_t)(server_t *server, client_t *client, char *input);

void login_command(server_t *server, client_t *client, char *input);
void logout_command(server_t *server, client_t *client, char *input);
void users_command(server_t *server, client_t *client, char *input);
void user_command(server_t *server, client_t *client, char *input);
void send_command(server_t *server, client_t *client, char *input);
void messages_command(server_t *server, client_t *client, char *input);
void use_command(server_t *server, client_t *client, char *input);
void create_command(server_t *server, client_t *client, char *input);
void list_command(server_t *server, client_t *client, char *input);
void subscribe_command(server_t *server, client_t *client, char *input);
void unsubscribe_command(server_t *server, client_t *client, char *input);
void subscribed_command(server_t *server, client_t *client, char *input);
void info_command(server_t *server, client_t *client, char *input);

typedef struct command_s {
    packet_command_t id;
    command_func_t function;
    bool auth;
} command_t;

static const command_t COMMANDS[] = {
        { COMMAND_LOGIN, &login_command, false, },
        { COMMAND_LOGOUT, &logout_command, true, },
        { COMMAND_USER, &user_command, true },
        { COMMAND_USERS, &users_command, true },
        { COMMAND_SEND, &send_command, true },
        { COMMAND_MESSAGES, &messages_command, true },
        { COMMAND_USE, &use_command, true },
        { COMMAND_CREATE, &create_command, true },
        { COMMAND_LIST, &list_command, true },
        { COMMAND_SUBSCRIBE, &subscribe_command, true },
        { COMMAND_UNSUBSCRIBE, &unsubscribe_command, true },
        { COMMAND_SUBSCRIBED, &subscribed_command, true },
        { COMMAND_INFO, &info_command, true },
};

#endif
