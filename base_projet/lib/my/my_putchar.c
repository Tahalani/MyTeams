/*
** EPITECH PROJECT, 2021
** my_putchar
** File description:
** affiche un char
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
