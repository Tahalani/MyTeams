/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** use
*/

#include <string.h>
#include <unistd.h>

#include "constants.h"
#include "packets.h"
#include "server.h"
#include "types.h"

static void init_data(char **data)
{
    memset(data[0], 0, UUID_LENGTH + 1);
    memset(data[1], 0, UUID_LENGTH + 1);
    memset(data[2], 0, UUID_LENGTH + 1);
}

static int read_args(client_t *client, char **data, command_packet_t *packet)
{
    int count = 0;
    int times = (int) packet->data_size / UUID_LENGTH;
    size_t max = UUID_LENGTH * 3;
    ssize_t re = 0;

    if (packet->data_size % UUID_LENGTH != 0 || packet->data_size > max) {
        send_message_packet(client->fd, 500);
        clear_buffer(client->fd, packet);
        return -1;
    }
    for (count = 0; count < times; count++) {
        re = read(client->fd, data[count], UUID_LENGTH);
        if (re != UUID_LENGTH) {
            send_message_packet(client->fd, 500);
            return -1;
        }
    }
    if (count > 3)
        send_message_packet(client->fd, 500);
    return count > 3 ? -1 : count;
}

void use_command(server_t *server, client_t *client, \
    command_packet_t *packet)
{
    char uuid1[UUID_LENGTH + 1];
    char uuid2[UUID_LENGTH + 1];
    char uuid3[UUID_LENGTH + 1];
    char *data[3] = { uuid1, uuid2, uuid3 };
    int len = 0;

    init_data(data);
    len = read_args(client, data, packet);
    if (len == -1)
        return;
    if (len == 0)
        fill_default_use(client);
    else if (len == 1)
        fill_team_use(client, data);
    if (len == 2)
        fill_channel_use(server, client, data);
    else if (len == 3)
        fill_thread_use(server, client, data);
    send_context_packet(client->fd, len);
    send_message_packet(client->fd, 200);
}
