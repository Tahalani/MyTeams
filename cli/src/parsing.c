/*
** EPITECH PROJECT, 2023
** parsing.c
** File description:
** parsing.c
*/

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char **str_to_word(char *str, char c);

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

static char *cpy_args(char const *input)
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
    return (args);
}

static char **get_args(char const *input, const int quote)
{
    char **args = malloc(sizeof(char *) * (quote + 1));
    int is_quote = 0;
    int k = 0;

    if (args == NULL)
        return (NULL);
    for (size_t i = 0; input[i] != '\0'; i++) {
        if (input[i] == '"')
            is_quote = (is_quote == 0) ? 1 : 0;
        // if (is_quote == 0 && input[i] != ' ') {
        //     return (NULL);
        // }
        else if (is_quote == 1) {
            args[k] = cpy_args(input + i);
            k++;
            i += strlen(args[k - 1]);
            is_quote = 0;
        }
    }
    args[quote] = NULL;
    return (args);
}

void display_arg(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        printf("array: %s\n", array[i]);
}

char **parsing_input(char *input, bool *noArgs)
{
    char **args = str_to_word(input, ' ');
    int quote = count_quote(input);

    if (args[1] == NULL) {
        printf("No arguments given\n");
        *noArgs = true;
        return (NULL);
    }
    if (quote == -1)
        return (NULL);
    args = get_args(input, quote);
    // display_arg(args);
    return (args);
}
