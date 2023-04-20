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
    #include <time.h>

    #include "constants.h"

typedef char packet_header_t;

typedef enum packet_type_e {
    PACKET_MESSAGE,
    PACKET_CONTEXT,
    PACKET_TEAM,
    PACKET_CHANNEL,
    PACKET_THREAD,
    PACKET_REPLY,
    PACKET_USER,
    PACKET_ERROR,
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

typedef enum packet_context_e {
    CONTEXT_NONE,
    CONTEXT_TEAM,
    CONTEXT_CHANNEL,
    CONTEXT_THREAD,
} packet_context_t;

typedef enum packet_error_e {
    ERROR_UNAUTHORIZED,
    ERROR_ALREADY_EXIST,
    ERROR_UNKNOWN_TEAM,
    ERROR_UNKNOWN_CHANNEL,
    ERROR_UNKNOWN_THREAD,
    ERROR_UNKNOWN_USER,
} packet_error_t;

typedef struct PACKED command_packet_s {
    packet_command_t command;
    size_t data_size;
} command_packet_t;

typedef struct PACKED message_packet_s {
    int code;
} message_packet_t;

typedef struct PACKED context_packet_s {
    packet_context_t context;
} context_packet_t;

typedef struct PACKED team_packet_s {
    char uuid[UUID_LENGTH + 1];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    packet_command_t context;
} team_packet_t;

typedef team_packet_t channel_packet_t;

typedef struct PACKED thread_packet_s {
    char uuid[UUID_LENGTH + 1];
    char name[MAX_NAME_LENGTH + 1];
    char message[MAX_BODY_LENGTH + 1];
    char team_uuid[UUID_LENGTH + 1];
    time_t created_at;
    packet_command_t context;
} thread_packet_t;

typedef struct PACKED reply_packet_s {
    char body[MAX_BODY_LENGTH + 1];
    char author[UUID_LENGTH + 1];
    char target[UUID_LENGTH + 1];
    char team_uuid[UUID_LENGTH + 1];
    time_t created_at;
    packet_command_t context;
} reply_packet_t;

typedef struct PACKED user_packet_s {
    char uuid[UUID_LENGTH + 1];
    char username[MAX_NAME_LENGTH + 1];
    bool status;
    packet_command_t context;
} user_packet_t;

typedef struct PACKED error_packet_s {
    packet_error_t error;
    char uuid[UUID_LENGTH + 1];
} error_packet_t;

#endif
