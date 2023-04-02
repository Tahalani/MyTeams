/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** packets.h
*/

#ifndef PACKETS_H
    #define PACKETS_H

    #include <stdbool.h>

typedef char packet_header_t;

typedef enum packet_type_e {
    PACKET_MESSAGE,
    PACKET_USER,
} packet_type_t;

typedef struct message_packet_s {
    int code;
} message_packet_t;

typedef struct user_packet_s {
    char uuid[37];
    char username[33];
    bool status;
} user_packet_t;

#endif
