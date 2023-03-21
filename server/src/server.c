/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** server.c
*/

#include <stdio.h>
#include <string.h>

static void display_help_server(char *binary)
{
    printf("USAGE: %s port\n", binary);
    printf("\tport\tis the port number on which the server socket listens.\n");
}

int teams_server(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        display_help_server(av[0]);
        return 0;
    }
    printf("Hello world!\n");
    return 0;
}
