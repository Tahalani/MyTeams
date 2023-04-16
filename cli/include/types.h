/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** types.h
*/

#ifndef TYPES_H_
    #define TYPES_H_

    #include "packets.h"

typedef struct client_s {
    int fd;
    char *user_uuid;
    char *user_name;
    packet_context_t context;
} client_t;

#endif
