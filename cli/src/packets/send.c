/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** packets.c
*/

#include <stdio.h>
#include <unistd.h>

#include "cli.h"
#include "commands.h"
#include "messages.h"
#include "packets.h"

void send_rfc_message(int code)
{
    for (size_t i = 0; i < MESSAGES_COUNT; i++) {
        if (MESSAGES[i].code == code) {
            printf("%s\n", MESSAGES[i].message);
            return;
        }
    }
    fprintf(stderr, "Unknown RFC message code: %d\n", code);
}

void send_packet(int fd, packet_command_t type, size_t data_size, char *data)
{
    command_packet_t packet = { type, data_size };

    write(fd, &packet, sizeof(command_packet_t));
    if (data != NULL) {
        write(fd, data, data_size);
    }
}

void send_help_message(void)
{
    char space = '\0';

    printf("The following commands are recognized.\n");
    for (size_t i = 0; i < COMMANDS_COUNT; i++) {
        space = ' ';
        if ((i % 5 == 0 && i != 0) || (i == COMMANDS_COUNT - 1))
            space = '\n';
        printf( "%s%c", COMMANDS[i].name, space);
    }
}
