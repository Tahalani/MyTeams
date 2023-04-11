/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** team
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "server.h"

int get_fd_file(char *name)
{
    char *path = NULL;
    int fd = -1;

    asprintf(&path, "server/database/Team/%s", name);
    fd = open(path, O_CREAT | O_RDWR, 0744);
    if (fd == -1)
        perror("open");
    return fd;
}
