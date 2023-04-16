/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** basic.c
*/

#include <stddef.h>

#include "cli.h"
#include "constants.h"
#include "packets.h"
#include "types.h"

void help_command(UNUSED client_t *client, UNUSED char **args)
{
    send_help_message();
}

void info_command(client_t *client, UNUSED char **args)
{
    send_packet(client->fd, COMMAND_INFO, 0, NULL);
}

void list_command(client_t *client, UNUSED char **args)
{
    send_packet(client->fd, COMMAND_LIST, 0, NULL);
}

void users_command(client_t *client, UNUSED char **args)
{
    send_packet(client->fd, COMMAND_USERS, 0, NULL);
}
