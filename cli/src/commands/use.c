/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** interaction.c
*/

#include <string.h>

#include "cli.h"
#include "constants.h"
#include "packets.h"
#include "types.h"

static int check_context(char *args, char *array)
{
    int res = 0;
    char *uuid = strtok(args, " ");

    memset(array, 0, UUID_LENGTH * 3);
    for (res = 0; uuid != NULL; res++) {
        if (!is_uuid(uuid)) {
            send_rfc_message(402);
            return -1;
        }
        if (res < 3) {
            strcat(array, uuid);
        }
        uuid = strtok(NULL, " ");
    }
    if (res < 1 || res > 3) {
        send_rfc_message(400);
        return -1;
    }
    return res;
}

void use_command(client_t *client, char *args)
{
    char data[UUID_LENGTH * 3 + 1];
    int context = check_context(args, data);

    if (context == -1) {
        return;
    }
    send_packet(client->fd, COMMAND_USE, UUID_LENGTH * context, data);
}
