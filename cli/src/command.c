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

bool handle_message(int socket_fd)
{
    char buffer[1024];
    ssize_t re = read(socket_fd, buffer, 1024);

    if (re == -1) {
        return false;
    }
    if (re == 0) {
        return true;
    }
    write(1, buffer, re);
    return false;
}
