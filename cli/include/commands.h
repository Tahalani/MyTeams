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

typedef void (*command_func_t)(client_t *client, char **args);

void login_command(client_t *client, char **args);
void logout_command(client_t *client, char **args);
void users_command(client_t *client, char **args);
void user_command(client_t *client, char **args);
void send_command(client_t *client, char **args);
void messages_command(client_t *client, char **args);
void use_command(client_t *client, char **args);
void create_command(client_t *client, char **args);
void list_command(client_t *client, char **args);
void subscribe_command(client_t *client, char **args);
void unsubscribe_command(client_t *client, char **args);
void subscribed_command(client_t *client, char **args);
void info_command(client_t *client, char **args);
void help_command(client_t *client, char **args);

typedef struct command_s {
    char *name;
    command_func_t function;
    int args;
} command_t;

static const command_t COMMANDS[] = {
        { "/create", &create_command, -1 },
        { "/help", &help_command, 0 },
        { "/info", &info_command, 0 },
        { "/login", &login_command, 1  },
        { "/logout", &logout_command, 0 },
        { "/list", &list_command, 0 },
        { "/messages", &messages_command, 0 },
        { "/send", &send_command, 1 },
        { "/subscribe", &subscribe_command, 1 },
        { "/subscribed", &subscribed_command, 0 },
        { "/unsubscribe", &unsubscribe_command, 1 },
        { "/use", &use_command, -1 },
        { "/user", &user_command, 1 },
        { "/users", &users_command, 0 },
};

#endif
