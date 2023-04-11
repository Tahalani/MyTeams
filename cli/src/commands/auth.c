/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** auth.c
*/

#include <string.h>

#include "cli.h"
#include "constants.h"
#include "packets.h"
#include "types.h"

void login_command(client_t *client, char *args)
{
    char name[MAX_NAME_LENGTH + 1];

    if (strlen(args) == 0) {
        send_rfc_message(400);
    } else if (strlen(args) > MAX_NAME_LENGTH) {
        send_rfc_message(420);
    } else {
        memset(name, 0, MAX_NAME_LENGTH + 1);
        strcat(name, args);
        send_packet(client->fd, COMMAND_LOGIN, MAX_NAME_LENGTH, name);
    }
}

void logout_command(client_t *client, char *args)
{
    if (strlen(args) != 0) {
        send_rfc_message(400);
    } else {
        send_packet(client->fd, COMMAND_LOGOUT, 0, NULL);
    }
}
