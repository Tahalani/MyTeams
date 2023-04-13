/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** handler.h
*/

#ifndef HANDLER_H
    #define HANDLER_H

    #define HANDLER_COUNT (sizeof(HANDLERS) / sizeof(handler_t))

typedef void (*packet_handler_t)(client_t *client);

void message_packet_handler(client_t *client);
void user_packet_handler(client_t *client);
char **get_arguments(char *input);

typedef struct handler_s {
    char opcode;
    packet_handler_t function;
} handler_t;

static const handler_t HANDLERS[] = {
        { 0, &message_packet_handler, },
        { 1, &user_packet_handler },
};

#endif
