/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** display
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "database.h"

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
