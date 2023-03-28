/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** auth.c
*/

#include "commands.h"
#include "server.h"

void login_command(server_t *server, client_t *client, char *input)
{
    (void) server;
    (void) input;
    send_basic_message(client->fd, "200");
}
