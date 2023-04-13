/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** util.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"

static bool is_hexadecimal(char c)
{
    bool digit = c >= '0' && c <= '9';
    bool lower = c >= 'a' && c <= 'f';
    bool upper = c >= 'A' && c <= 'F';

    return digit || lower || upper;
}

bool is_uuid(char *str)
{
    bool is_dot = false;

    if (strlen(str) != 36) {
        return false;
    }
    for (int i = 0; i < 36; i++) {
        is_dot = (i == 8 || i == 13 || i == 18 || i == 23);
        if (is_dot && str[i] != '-') {
            return false;
        }
        if (!is_dot && !is_hexadecimal(str[i])) {
            return false;
        }
    }
    return true;
}

void fatal_error(const char *error)
{
    fprintf(stderr, "%s\n", error);
    exit(FAILURE);
}
