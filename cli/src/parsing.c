/*
** EPITECH PROJECT, 2023
** parsing.c
** File description:
** parsing.c
*/

#include <stdlib.h>
#include <string.h>

#include "cli.h"

static int count_quote(char const *str)
{
    int count = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '"')
            count++;
    }
    if (count % 2 != 0 || count <= 0)
        return (-1);
    return (count / 2);
}

static char *cpy_args(char const *input, size_t *index)
{
    char *args = NULL;
    int size_arg = 0;
    int k = 0;

    for (; input[size_arg] != '"'; size_arg++);
    args = malloc(sizeof(char) * (size_arg + 1));
    if (args == NULL)
        return (NULL);
    for (size_t i = 0; input[i] != '"'; i++, k++)
        args[k] = input[i];
    args[k] = '\0';
    *index += strlen(args);
    return (args);
}

static char **get_args(char const *input, const int quote)
{
    char **args = malloc(sizeof(char *) * (quote + 1));
    int is_quote = 0;
    int k = 0;

    if (args == NULL)
        fatal_error("malloc failed");
    for (size_t i = 0; input[i] != '\0'; i++) {
        if (input[i] == '"') {
            is_quote = (is_quote == 0) ? 1 : 0;
            continue;
        }
        if (is_quote == 0 && input[i] != ' ' && input[i] != '\t')
            return (NULL);
        if (is_quote == 1) {
            args[k++] = cpy_args(input + i, &i);
            is_quote = 0;
        }
    }
    args[quote] = NULL;
    return (args);
}

char **get_arguments(char *input)
{
    char **args = str_to_word(input, ' ');
    int quote = count_quote(input);
    size_t param = 0;

    if (args[1] == NULL) {
        free(args[0]);
        args[0] = NULL;
        return args;
    }
    if (quote == -1)
        return (NULL);
    param = strchr(input, ' ') - input;
    free_array(args);
    return get_args(input + param, quote);
}
