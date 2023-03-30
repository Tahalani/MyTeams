/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** commands.c
*/

#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "server.h"

static void handle_unknown(client_t *client)
{
    if (client->user == NULL) {
        send_basic_message(client->fd, "500");
    } else {
        send_basic_message(client->fd, "530");
    }
}

static void run_command(const command_t *command, server_t *ftp,
    client_t *client, char *input)
{
    if (command->auth && client->user == NULL) {
        send_basic_message(client->fd, "530");
        return;
    }
    command->function(ftp, client, input);
}

static void handle_command(server_t *server, client_t *client, char *input)
{
    char *identifier = strdup(input);
    char *name = NULL;

    if (identifier == NULL)
        return;
    name = strtok(identifier, " ");
    if (name == NULL) {
        handle_unknown(client);
        free(identifier);
        return;
    }
    for (size_t i = 0; i < COMMANDS_COUNT; i++) {
        if (strcmp(name, COMMANDS[i].name) == 0) {
            run_command(&COMMANDS[i], server, client, input);
            return;
        }
    }
    handle_unknown(client);
    free(identifier);
}

void handle_input(server_t *server, client_t *client, char *input)
{
    char *save_ptr = input;
    char *current = strtok_r(input, "\r\n", &save_ptr);

    if (current == NULL)
        return;
    while (current != NULL) {
        handle_command(server, client, current);
        current = strtok_r(NULL, "\r\n", &save_ptr);
    }
}
