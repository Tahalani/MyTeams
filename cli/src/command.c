/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** command.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "handler.h"

static void process_packet(int socket_fd, char opcode)
{
    const char *format = "Unknown packet sent by server with opcode %d\n";

    for (size_t i = 0; i < HANDLER_COUNT; i++) {
        if (HANDLERS[i].opcode == opcode) {
            HANDLERS[i].function(socket_fd);
            return;
        }
    }
    fprintf(stderr, format, opcode);
}

bool handle_input(int socket_fd)
{
    char *line = NULL;
    size_t size = 0;
    ssize_t len = getline(&line, &size, stdin);

    if (len == -1) {
        return true;
    } else {
        dprintf(socket_fd, "%s\r\n", line);
    }
    free(line);
    return false;
}

bool handle_packet(int socket_fd)
{
    char opcode;
    ssize_t re = read(socket_fd, &opcode, 1);

    if (re == -1) {
        return false;
    }
    if (re == 0) {
        return true;
    }
    process_packet(socket_fd, opcode);
    return false;
}
