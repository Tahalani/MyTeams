/*
** EPITECH PROJECT, 2021
** my_strlowcase
** File description:
** strlowcase
*/

#include <stddef.h>

char *my_strlowcase(char *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
    return (str);
}
