/*
** EPITECH PROJECT, 2021
** my_char_is_num
** File description:
** char is num
*/

int my_char_isnum(char a)
{
    if (a > '9' || a < '0')
        return (0);
    else
        return (1);
}
