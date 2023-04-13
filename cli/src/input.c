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

#include "commands.h"
#include "handler.h"
#include "cli.h"
#include "types.h"

static void execute_command(const command_t *command, client_t *client, \
    char **args)
{
    size_t args_size = array_len(args);

    if (command->auth && client->user_name == NULL) {
        send_rfc_message(430);
        return;
    } else if (command->args != -1 && command->args != (int) args_size) {
        send_rfc_message(400);
        return;
    }
    command->function(client, args);
}

static void handle_command(client_t *client, char *input)
{
    bool done = false;
    char **args = get_arguments(input);
    char *command = strtok(input, " ");

    if (command == NULL) {
        return;
    } else if (args == NULL) {
        send_rfc_message(401);
        return;
    }
    for (size_t i = 0; i < COMMANDS_COUNT && !done; i++) {
        if (strcmp(command, COMMANDS[i].name) == 0) {
            execute_command(&COMMANDS[i], client, args);
            done = true;
        }
    }
    if (!done) {
        send_rfc_message(client->user_name == NULL ? 430 : 404);
    }
    free_array(args);
}

static void process_packet(client_t *client, char opcode)
{
    const char *format = "Unknown packet sent by server with opcode %d\n";

    for (size_t i = 0; i < HANDLER_COUNT; i++) {
        if (HANDLERS[i].opcode == opcode) {
            HANDLERS[i].function(client);
            return;
        }
    }
    fprintf(stderr, format, opcode);
}

bool handle_input(client_t *client)
{
    char *line = NULL;
    size_t size = 0;
    ssize_t len = getline(&line, &size, stdin);

    if (len < 1) {
        return true;
    } else {
        line[len - 1] = '\0';
        handle_command(client, line);
    }
    free(line);
    return false;
}

bool handle_packet(client_t *client)
{
    char opcode;
    ssize_t re = read(client->fd, &opcode, 1);

    if (re == -1) {
        return false;
    }
    if (re == 0) {
        return true;
    }
    process_packet(client, opcode);
    return false;
}
