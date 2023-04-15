/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** errors.c
*/

#include <unistd.h>

#include "cli.h"
#include "constants.h"
#include "handler.h"
#include "logging_client.h"
#include "packets.h"
#include "types.h"

int handle_unauthorized(UNUSED const char *uuid)
{
    return client_error_unauthorized();
}

int handle_already_exsist(UNUSED const char *uuid)
{
    return client_error_already_exist();
}

void error_packet_handler(client_t *client)
{
    error_packet_t packet;
    ssize_t re = read(client->fd, &packet, sizeof(error_packet_t));

    if (re != sizeof(error_packet_t)) {
        return;
    }
    for (size_t i = 0; i < ERR_HANDLER_COUNT; i++) {
        if (ERROR_HANDLERS[i].error == packet.error) {
            ERROR_HANDLERS[i].function(packet.uuid);
            return;
        }
    }
    send_rfc_message(500);
}
