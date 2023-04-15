/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** interaction.c
*/

#include <string.h>
#include <stdbool.h>

#include "cli.h"
#include "constants.h"
#include "packets.h"
#include "types.h"

static bool concat_uuid(char *uuid, char *data)
{
    if (!is_uuid(uuid)) {
        return false;
    }
    strcat(data, uuid);
    return true;
}

void use_command(client_t *client, char **args)
{
    char data[UUID_LENGTH * 3 + 1];
    size_t len = array_len(args);

    if (len > 3) {
        send_rfc_message(400);
        return;
    }
    for (size_t i = 0; i < len; i++) {
        if (!concat_uuid(args[i], data)) {
            send_rfc_message(420);
            return;
        }
    }
    send_packet(client->fd, COMMAND_USE, UUID_LENGTH * len, data);
}
