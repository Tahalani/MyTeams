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
    #include "types.h"

typedef void (*command_func_t)(server_t *server, client_t *client, char *input);

void login_command(server_t *server, client_t *client, char *input);
void logout_command(server_t *server, client_t *client, char *input);
void users_command(server_t *server, client_t *client, char *input);
void user_command(server_t *server, client_t *client, char *input);
void send_command(server_t *server, client_t *client, char *input);
void subscribe_command(server_t *server, client_t *client, char *input);
void unsubscribe_command(server_t *server, client_t *client, char *input);

typedef struct command_s {
    char *name;
    command_func_t function;
    bool auth;
} command_t;

static const command_t COMMANDS[] = {
        { "/login", &login_command, false, },
        { "/logout", &logout_command, true, },
        { "/users", &users_command, true },
        { "/user", &user_command, true },
        { "/send", &send_command, true },
        { "/subscribe", &subscribe_command, true },
        { "/unsubscribe", &unsubscribe_command, true },
};

#endif
