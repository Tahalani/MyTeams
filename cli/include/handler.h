/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** handler.h
*/

#ifndef HANDLER_H
    #define HANDLER_H

    #define HANDLER_COUNT (sizeof(HANDLERS) / sizeof(handler_t))
    #define ERR_HANDLER_COUNT (sizeof(ERROR_HANDLERS) / sizeof(error_handler_t))

    #include "logging_client.h"
    #include "types.h"

typedef void (*packet_handler_t)(client_t *client);
typedef int (*packet_error_handler_t)(const char *uuid);

void message_packet_handler(client_t *client);
void context_packet_handler(client_t *client);
void user_packet_handler(client_t *client);
void error_packet_handler(client_t *client);

int handle_unauthorized(const char *uuid);
int handle_already_exsist(const char *uuid);

typedef struct handler_s {
    char opcode;
    packet_handler_t function;
} handler_t;

typedef struct error_handler_s {
    packet_error_t error;
    packet_error_handler_t function;
} error_handler_t;

static const handler_t HANDLERS[] = {
        { PACKET_MESSAGE, &message_packet_handler, },
        { PACKET_CONTEXT, &context_packet_handler, },
        { PACKET_USER, &user_packet_handler },
        { PACKET_ERROR, &error_packet_handler },
};

static const error_handler_t ERROR_HANDLERS[] = {
        { ERROR_UNAUTHORIZED, &handle_unauthorized },
        { ERROR_ALREADY_EXIST, &handle_already_exsist },
        { ERROR_UNKNOWN_TEAM, &client_error_unknown_team },
        { ERROR_UNKNOWN_CHANNEL, &client_error_unknown_channel },
        { ERROR_UNKNOWN_THREAD, &client_error_unknown_thread },
        { ERROR_UNKNOWN_USER, &client_error_unknown_user },
};

#endif
