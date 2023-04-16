/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** fixme.c
*/

#include <string.h>
#include <stdbool.h>

#include "cli.h"
#include "constants.h"
#include "packets.h"
#include "types.h"

void user_command(client_t *client, char **args)
{
    char uuid[UUID_LENGTH + 1];

    memset(uuid, 0, UUID_LENGTH + 1);
    if (!concat_uuid(args[0], uuid)) {
        send_rfc_message(420);
        return;
    }
    send_packet(client->fd, COMMAND_USER, UUID_LENGTH, uuid);
}

void send_command(client_t *client, char **args)
{
    size_t size = UUID_LENGTH + MAX_BODY_LENGTH;
    char data[size + 1];

    memset(data, 0, size + 1);
    if (strlen(args[0]) > UUID_LENGTH) {
        send_rfc_message(421);
        return;
    }
    if (strlen(args[1]) > MAX_BODY_LENGTH) {
        send_rfc_message(423);
        return;
    }
    strcat(data, args[0]);
    strcat(&data[UUID_LENGTH], args[1]);
    send_packet(client->fd, COMMAND_SEND, size, data);
}

void messages_command(client_t *client, char **args)
{
    char uuid[UUID_LENGTH + 1];

    memset(uuid, 0, UUID_LENGTH + 1);
    if (!concat_uuid(args[0], uuid)) {
        send_rfc_message(420);
        return;
    }
    send_packet(client->fd, COMMAND_MESSAGES, UUID_LENGTH, uuid);
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
