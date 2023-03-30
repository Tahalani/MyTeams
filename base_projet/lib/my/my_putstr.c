/*
** EPITECH PROJECT, 2021
** My_putstr
** File description:
** My_putstr
*/

#include <unistd.h>

int my_strlen(char const *str);

void my_putchar(char c);

int my_putstr(char const *str)
{
    for (; *str != '\0'; str++){
        my_putchar(*str);
    }
    return (0);
}

void my_put_error(char const *str)
{
    write(2, &str, my_strlen(str));
}
