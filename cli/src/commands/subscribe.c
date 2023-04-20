/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** fixme2.c
*/

#include <string.h>

#include "cli.h"
#include "constants.h"
#include "packets.h"
#include "types.h"

void subscribe_command(client_t *client, char **args)
{
    char uuid[UUID_LENGTH + 1];

    memset(uuid, 0, UUID_LENGTH + 1);
    if (!concat_uuid(args[0], uuid)) {
        send_rfc_message(420);
        return;
    }
    send_packet(client->fd, COMMAND_SUBSCRIBE, UUID_LENGTH, uuid);
}

void unsubscribe_command(client_t *client, char **args)
{
    char uuid[UUID_LENGTH + 1];

    memset(uuid, 0, UUID_LENGTH + 1);
    if (!concat_uuid(args[0], uuid)) {
        send_rfc_message(420);
        return;
    }
    send_packet(client->fd, COMMAND_UNSUBSCRIBE, UUID_LENGTH, uuid);
}

void subscribed_command(client_t *client, char **args)
{
    char data[UUID_LENGTH + 1];
    size_t len = array_len(args);

    memset(data, 0, UUID_LENGTH + 1);
    if (len > 1) {
        send_rfc_message(400);
        return;
    }
    if (len == 1 && !concat_uuid(args[0], data)) {
        send_rfc_message(420);
        return;
    }
    send_packet(client->fd, COMMAND_SUBSCRIBED, UUID_LENGTH * len, data);
}
