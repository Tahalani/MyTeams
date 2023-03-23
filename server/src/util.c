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

void fatal_error(char *error)
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
