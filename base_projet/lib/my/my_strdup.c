/*
** EPITECH PROJECT, 2021
** my_strdup
** File description:
** my_strdup
*/

#include <stdlib.h>
#include "my.h"

int my_strlen(char const *str);

int my_putstr(char const *str);

char *my_strdup(char const *src)
{
    int size = my_strlen(src);
    char *new_str = NULL;
    int i = 0;

    new_str = malloc(sizeof(char) * (size + 1));
    for (i = 0; src[i] != '\0'; i++)
        new_str[i] = src[i];
    new_str[i] = '\0';
    return new_str;
}
