/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** help.c
*/

#include <string.h>

#include "cli.h"
#include "types.h"

void help_command(client_t *client, char *args)
{
    if (strlen(args) != 0) {
        send_rfc_message(400);
    } else {
        send_help_message();
    }
}
