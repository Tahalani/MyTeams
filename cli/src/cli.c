/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** server.c
*/

#include <stdio.h>
#include <string.h>

static void display_help_client(char *binary)
{
    printf("USAGE: %s ip port\n", binary);
    printf("\tip\tis the server ip address on which the server socket listens.\n");
    printf("\tport\tis the port number on which the server socket listens.\n");
}

int teams_cli(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        display_help_client(av[0]);
        return 0;
    }
    printf("Hello world!\n");
    return 0;
}
