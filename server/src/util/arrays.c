/*
** EPITECH PROJECT, 2022
** strrr
** File description:
** strrr
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

int verif_char(char x, char separator)
{
    if (x == separator)
        return 0;
    return 1;
}

int count_word(char const *str, char separator)
{
    int i = 0;
    int count = 1;

    for (; str[i] != '\0'; i++) {
        if (verif_char(str[i], separator) == 1 && verif_char(str[i + 1],
            separator) == 0)
            count++;
    }
    return (count);
}

int size_word(char const *str, int i, char separator)
{
    int count = 0;

    for (; str[i] != separator && str[i] != '\0'; i++)
        count++;
    return (count);
}

char **str_to_word(char const *str, char separator)
{
    char **tab = NULL;
    int i = 0;
    int size = 0;
    int count = count_word(str, separator);

    tab = malloc(sizeof(char *) * (count + 1));
    tab[count] = NULL;
    for (int y = 0; y != count; y++) {
        for (; str[i] == separator; i++);
        size = size_word(str, i, separator);
        tab[y] = malloc(sizeof(char) * (size + 1));
        tab[y][size] = '\0';
        for (int x = 0; x != size; x++) {
            tab[y][x] = str[i];
            i++;
        }
        i++;
    }
    return (tab);
}
