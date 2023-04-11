/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** messages.c
*/

#include <string.h>

#include "constants.h"
#include "messages.h"
#include "server.h"

// TODO: Delete this file will disappear when packet handling is done
void send_basic_message(UNUSED int fd, char *code)
{
    const char *msg = NULL;

    for (int i = 0; MESSAGES[i] != NULL; i++) {
        if (strncmp(MESSAGES[i], code, 3) == 0)
            msg = MESSAGES[i];
    }
    if (msg != NULL) {

    }
}
