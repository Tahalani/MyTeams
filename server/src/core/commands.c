/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** commands.c
*/

#include <unistd.h>

#include "commands.h"
#include "packets.h"
#include "server.h"
#include "types.h"

static void run_command(const command_t *command, server_t *server, \
    client_t *client, command_packet_t *packet)
{
    if (command->auth && client->user == NULL) {
        send_error_packet(client->fd, ERROR_UNAUTHORIZED, NULL);
        clear_buffer(client->fd, packet);
        return;
    }
    command->function(server, client, packet);
}

void clear_buffer(int fd, command_packet_t *packet)
{
    char buffer[packet->data_size];
    ssize_t re = read(fd, buffer, packet->data_size);

    if (re != (ssize_t) packet->data_size) {
        send_message_packet(fd, 500);
    }
}

void handle_input(server_t *server, client_t *client, \
    command_packet_t *packet)
{
    for (size_t i = 0; i < COMMANDS_COUNT; i++) {
        if (COMMANDS[i].id == packet->command) {
            run_command(&COMMANDS[i], server, client, packet);
            return;
        }
    }
    send_message_packet(client->fd, 500);
    clear_buffer(client->fd, packet);
}
