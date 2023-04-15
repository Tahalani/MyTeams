/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** display
*/

#include "server.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int get_fd_file(char *name)
{
    char *path = NULL;
    int fd = -1;

    asprintf(&path, "server/database/%s", name);
    fd = open(path, O_CREAT | O_RDWR, 0744);
    if (fd == -1)
        perror("open");
    return fd;
}

relation_t *load_relation(int fd)
{
    relation_t *relation = malloc(sizeof(relation_t));
    ssize_t re = 0;

    memset(relation, 0, sizeof(relation_t));
    re = read(fd, relation, sizeof(relation_t));
    if (re != sizeof(relation_t)) {
        free(relation);
        return NULL;
    }
    return relation;
}
