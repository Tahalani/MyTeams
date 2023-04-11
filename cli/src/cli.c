/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** server.c
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "constants.h"

static bool check_arguments(char **argv)
{
    struct in_addr in;
    char *end = NULL;
    int address = inet_aton(argv[1], &in);
    long parsed = strtol(argv[2], &end, 10);

    if (address == -1) {
        perror("invalid address");
        return false;
    }
    if (strlen(end) > 0) {
        fprintf(stderr, "Error: Port must be a number\n");
        return false;
    }
    if (parsed < 1 || parsed > 65535) {
        fprintf(stderr, "Error: Port is invalid\n");
        return false;
    }
    return true;
}

static void display_help_client(char *binary)
{
    printf("USAGE: %s ip port\n", binary);
    printf("\tip\tis the server ip address ");
    printf("on which the server socket listens.\n");
    printf("\tport\tis the port number ");
    printf("on which the server socket listens.\n");
}

int teams_cli(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        display_help_client(argv[0]);
        return SUCCESS;
    }
    if (argc != 3) {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        return FAILURE;
    } else if (!check_arguments(argv)) {
        return FAILURE;
    }
    return start_client(argv[1], atoi(argv[2])) ? SUCCESS : FAILURE;
}
