/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** packets.h
*/

#ifndef PACKETS_H
    #define PACKETS_H

    #include <stdbool.h>
    #include <stddef.h>
    #include "constants.h"

typedef char packet_header_t;

typedef enum packet_type_e {
    PACKET_MESSAGE,
    PACKET_USER,
} packet_type_t;

typedef enum packet_command_e {
    COMMAND_LOGIN,
    COMMAND_LOGOUT,
    COMMAND_USERS,
    COMMAND_USER,
    COMMAND_SEND,
    COMMAND_MESSAGES,
    COMMAND_SUBSCRIBE,
    COMMAND_SUBSCRIBED,
    COMMAND_UNSUBSCRIBE,
    COMMAND_USE,
    COMMAND_CREATE,
    COMMAND_LIST,
    COMMAND_INFO,
} packet_command_t;

typedef struct PACKED command_packet_s {
    packet_command_t command;
    size_t data_size;
} command_packet_t;

typedef struct PACKED message_packet_s {
    int code;
} message_packet_t;

typedef struct PACKED user_packet_s {
    char uuid[UUID_LENGTH + 1];
    char username[MAX_NAME_LENGTH + 1];
    bool status;
    packet_command_t context;
} user_packet_t;

#endif
