/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** use
*/

#include <stdbool.h>
#include <unistd.h>

#include "server.h"
#include "types.h"

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

void use_command(server_t *server, client_t *client, command_packet_t *packet)
{
    char uuid1[UUID_LENGTH + 1];
    char uuid2[UUID_LENGTH + 1];
    char uuid3[UUID_LENGTH + 1];
    char *data[3] = { uuid1, uuid2, uuid3 };
    int len = read_args(client, data, packet);
    bool done = false;

    if (len == 0)
        done = fill_default_use(client);
    else if (len == 1)
        done = fill_team_use(server, client, data);
    if (len == 2)
        done = fill_channel_use(server, client, data);
    else if (len == 3)
        done = fill_thread_use(server, client, data);
    if (done) {
        send_context_packet(client->fd, len);
        send_message_packet(client->fd, 200);
    }
}
