/*
** EPITECH PROJECT, 2021
** my_memset
** File description:
** Initialize a new string.
*/

#include <stdlib.h>

char *my_memset(char c, int n)
{
    char *res = malloc(sizeof(char) * (n + 1));
    int i = 0;

    for (i = 0; i != n; i++)
        res[i] = c;
    res[i + 1] = 0;
    return res;
}
