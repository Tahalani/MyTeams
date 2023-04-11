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

typedef void (*command_func_t)(client_t *client, char *args);

void login_command(client_t *client, char *args);
void logout_command(client_t *client, char *args);
void users_command(client_t *client, char *args);
void user_command(client_t *client, char *args);
void send_command(client_t *client, char *args);
void messages_command(client_t *client, char *args);
void use_command(client_t *client, char *args);
void create_command(client_t *client, char *args);
void list_command(client_t *client, char *args);
void subscribe_command(client_t *client, char *args);
void unsubscribe_command(client_t *client, char *args);
void subscribed_command(client_t *client, char *args);
void info_command(client_t *client, char *args);
void help_command(client_t *client, char *args);

typedef struct command_s {
    char *name;
    command_func_t function;
    bool auth;
} command_t;

static const command_t COMMANDS[] = {
        { "/create", &create_command, true },
        { "/help", &help_command, true },
        { "/info", &info_command, true },
        { "/login", &login_command, false, },
        { "/logout", &logout_command, true, },
        { "/list", &list_command, true },
        { "/messages", &messages_command, true },
        { "/send", &send_command, true },
        { "/subscribe", &subscribe_command, true },
        { "/subscribed", &subscribed_command, true },
        { "/unsubscribe", &unsubscribe_command, true },
        { "/use", &use_command, true },
        { "/user", &user_command, true },
        { "/users", &users_command, true },
};

#endif
