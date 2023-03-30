/*
** EPITECH PROJECT, 2021
** my_str_isnum
** File description:
** isnum
*/

int my_str_isnum(char const *str)
{
    for (int a = 0; str[a] != '\0'; a++) {
        if ((str[a] < '0' || str[a] > '9') && str[0] != '-')
            return (0);
    }
    return (1);
}
