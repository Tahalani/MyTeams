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

typedef void (*command_func_t)(server_t *server, client_t *client, \
    command_packet_t *packet);

void login_command(server_t *server, client_t *client, \
    command_packet_t *packet);
void logout_command(server_t *server, client_t *client, \
    command_packet_t *packet);
void users_command(server_t *server, client_t *client, \
    command_packet_t *packet);
void user_command(server_t *server, client_t *client, \
    command_packet_t *packet);
void send_command(server_t *server, client_t *client, \
    command_packet_t *packet);
void messages_command(server_t *server, client_t *client, \
    command_packet_t *packet);
void use_command(server_t *server, client_t *client, \
    command_packet_t *packet);
void create_command(server_t *server, client_t *client, \
    command_packet_t *packet);
void list_command(server_t *server, client_t *client, \
    command_packet_t *packet);
void subscribe_command(server_t *server, client_t *client, \
    command_packet_t *packet);
void unsubscribe_command(server_t *server, client_t *client, \
    command_packet_t *packet);
void subscribed_command(server_t *server, client_t *client, \
    command_packet_t *packet);
void info_command(server_t *server, client_t *client, \
    command_packet_t *packet);

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
