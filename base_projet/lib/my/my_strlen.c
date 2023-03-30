/*
** EPITECH PROJECT, 2021
** my_strlen
** File description:
** my_strlen
*/

int my_strlen(char const *str)
{
    int c = 0;

    for (; str[c] != '\0'; c++);
    return (c);
}
