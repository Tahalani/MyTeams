/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** server.h
*/

#ifndef CLI_H_
    #define CLI_H_

    #include <stdbool.h>

    #include "packets.h"
    #include "types.h"

int teams_cli(int argc, char **argv);

bool start_client(char *address, int port);

bool handle_input(client_t *client);
bool handle_packet(client_t *client);

void send_rfc_message(int code);
void send_packet(int fd, packet_command_t type, size_t data_size, char *data);
void send_help_message(void);

bool is_uuid(char *str);
char **get_arguments(char *input);
char **str_to_word(char const *str, char separator);
size_t array_len(char **array);
void free_array(char **array);
bool concat_uuid(char *uuid, char *data);

void fatal_error(const char *error);

#endif
