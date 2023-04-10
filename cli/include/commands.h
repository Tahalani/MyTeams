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
    #include "cli.h"

typedef void (*command_func_t)(client_t *client, char *input);

void login_command(client_t *client, char *input);
void logout_command(client_t *client, char *input);
void users_command(client_t *client, char *input);
void user_command(client_t *client, char *input);
void send_command(client_t *client, char *input);
void messages_command(client_t *client, char *input);
void use_command(client_t *client, char *input);
void create_command(client_t *client, char *input);
void list_command(client_t *client, char *input);
void subscribe_command(client_t *client, char *input);
void unsubscribe_command(client_t *client, char *input);
void subscribed_command(client_t *client, char *input);
void info_command(client_t *client, char *input);

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
        { "/messages", &messages_command, true },
        { "/use", &use_command, true },
        { "/create", &create_command, true },
        { "/list", &list_command, true },
        { "/subscribe", &subscribe_command, true },
        { "/unsubscribe", &unsubscribe_command, true },
        { "/subscribed", &subscribed_command, true },
        { "/info", &info_command, true },
};

#endif
