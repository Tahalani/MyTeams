/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** interaction.c
*/

#include <string.h>

#include "cli.h"
#include "types.h"

static int check_context(char *args)
{
    int res = 0;
    char *uuid = strtok(args, " ");

    if (strlen(args) == 0) {
        send_rfc_message(400);
        return -1;
    }
    for (res = 0; uuid != NULL; res++) {
        if (!is_uuid(uuid)) {
            send_rfc_message(402);
            return -1;
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
    int context = check_context(args);
    char data[UUID_LENGTH * 3 + 1];
    char *uuid = NULL;

    memset(data, 0, UUID_LENGTH * 3);
    if (context == -1) {
        return;
    }
    uuid = strtok(args, " ");
    for (int i = 0; i < context; i++) {
        if (uuid == NULL) {
            send_rfc_message(500);
            return;
        }
        strcat(data, uuid);
        uuid = strtok(NULL, " ");
    }
    send_packet(client->fd, COMMAND_USE, UUID_LENGTH * context, data);
}
