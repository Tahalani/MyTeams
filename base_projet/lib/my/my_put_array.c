/*
** EPITECH PROJECT, 2022
** base_projet
** File description:
** my_put_array
*/

#include <stddef.h>
#include "my.h"

void my_put_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        my_putstr(array[i]);
        my_putchar('\n');
    }
}
