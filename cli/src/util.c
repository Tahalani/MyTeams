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

void display_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        printf("%s\n", array[i]);
    }
}

char **parsing_input(char *input)
{
    char **args = NULL;
    char *param = NULL;
    int post_command = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '"' && post_command == 0)
            post_command = i;
        if (input[i] == '"')
            input[i] = ' ';
    }
    if (post_command == 0) {
        printf("bad\n");
        exit(84);
    }
    param = strdup(input + (post_command + 1));
    printf("test:%s:param\n", param);
    args = str_to_word(param, ' ');
    free(param);
    display_array(args);
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
