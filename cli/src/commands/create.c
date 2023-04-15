/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** create.c
*/

#include <string.h>

#include "cli.h"
#include "constants.h"
#include "packets.h"
#include "types.h"

static void create_title_desc(client_t *client, char **args, \
    size_t title_size, size_t desc_size)
{
    size_t size = title_size + desc_size;
    char data[size + 1];

    memset(data, 0, size + 1);
    if (array_len(args) != 2) {
        send_rfc_message(400);
        return;
    }
    if (strlen(args[0]) > title_size) {
        send_rfc_message(421);
        return;
    }
    if (strlen(args[1]) > desc_size) {
        send_rfc_message(422);
        return;
    }
    strcat(data, args[0]);
    strcat(&data[title_size], args[1]);
    send_packet(client->fd, COMMAND_CREATE, size, data);
}

static void create_body(client_t *client, char **args, size_t body_len)
{
    char data[body_len + 1];

    memset(data, 0, body_len + 1);
    if (array_len(args) != 1) {
        send_rfc_message(400);
        return;
    }
    if (strlen(args[0]) > body_len) {
        send_rfc_message(423);
        return;
    }
    strcat(data, args[0]);
    send_packet(client->fd, COMMAND_CREATE, body_len, data);
}

void create_command(client_t *client, char **args)
{
    switch (client->context) {
        case CONTEXT_NONE:
        case CONTEXT_TEAM:
            create_title_desc(client, args, MAX_NAME_LENGTH, \
                MAX_DESCRIPTION_LENGTH);
            break;
        case CONTEXT_CHANNEL:
            create_title_desc(client, args, MAX_NAME_LENGTH, MAX_BODY_LENGTH);
            break;
        case CONTEXT_THREAD:
            create_body(client, args, MAX_BODY_LENGTH);
            break;
        default:
            send_rfc_message(500);
            break;
    }
}
