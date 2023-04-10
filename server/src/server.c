/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** server.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "server.h"

static void display_help_server(char *binary)
{
    printf("USAGE: %s port\n", binary);
    printf("\tport\tis the port number ");
    printf("on which the server socket listens.\n");
}

static bool check_arguments(char **argv)
{
    char *end = NULL;
    long parsed = strtol(argv[1], &end, 10);

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

int teams_server(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        display_help_server(argv[0]);
        return SUCCESS;
    }
    if (argc != 2) {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        return FAILURE;
    } else if (!check_arguments(argv)) {
        return FAILURE;
    }
    return start_server(atoi(argv[1])) ? SUCCESS : FAILURE;
}
