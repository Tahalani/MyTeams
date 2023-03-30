/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** util.c
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void fatal_error(const char *error)
{
    fprintf(stderr, "%s\n", error);
    exit(FAILURE);
}

struct sockaddr *generate_address(int port, char *address)
{
    struct sockaddr_in *addr = malloc(sizeof(struct sockaddr_in));

    if (addr == NULL) {
        fatal_error("malloc failed");
    }
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = address == NULL ? INADDR_ANY : inet_addr(address);
    return (struct sockaddr *) addr;
}

char *generate_uuid(void)
{
    char *uuid = malloc(sizeof(char) * 37);
    char *base = "0123456789abcdef";

    if (uuid == NULL) {
        fatal_error("malloc failed");
    }
    for (int i = 0; i < 36; i++) {
        uuid[i] = base[rand() % 16];
    }
    uuid[8] = '-';
    uuid[13] = '-';
    uuid[18] = '-';
    uuid[23] = '-';
    uuid[36] = '\0';
    return uuid;
}
