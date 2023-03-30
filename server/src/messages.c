/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** messages.c
*/

#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "messages.h"
#include "server.h"

void send_basic_message(int fd, char *code)
{
    const char *msg = NULL;

    for (int i = 0; MESSAGES[i] != NULL; i++) {
        if (strncmp(MESSAGES[i], code, 3) == 0)
            msg = MESSAGES[i];
    }
    if (msg != NULL) {
        dprintf(fd, "%s%s", msg, CRLF);
    }
}

void send_help_message(int fd)
{
    char space = '\0';

    dprintf(fd, "214 The following commands are recognized.%s", CRLF);
    for (int i = 0; i < COMMANDS_COUNT; i++) {
        space = ' ';
        if ((i % 10 == 0 && i != 0) || (i == COMMANDS_COUNT - 1))
            space = '\n';
        dprintf(fd, "%s%c", COMMANDS[i].name, space);
    }
    dprintf(fd, "214 Help okay.%s", CRLF);
}