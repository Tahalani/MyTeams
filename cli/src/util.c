/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** util.c
*/

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char **str_to_word(char const *str, char separator);

static char **clear_args(char **args)
{
    for (size_t i = 0; args[i] != NULL; i++) {
        if (args[i][0] != '"' || args[i][strlen(args[i]) - 1] != '"')
            return (NULL);
        args[i] = strdup(args[i] + 1);
        args[i][strlen(args[i]) - 1] = '\0';
    }
    return (args);
}

char **parsing_input(char *input, bool *noArgs)
{
    char **args = str_to_word(input, ' ');
    char *param = NULL;
    int post_command = 0;

    if (args[1] == NULL) {
        printf("No arguments given\n");
        *noArgs = true;
        return (NULL);
    }
    post_command = strchr(input, '"') - input;
    if (post_command <= 0)
        return (NULL);
    param = strdup(input + post_command);
    args = str_to_word(param, ' ');
    args = clear_args(args);
    if (args == NULL)
        return (NULL);
    free(param);
    return (args);
}

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
