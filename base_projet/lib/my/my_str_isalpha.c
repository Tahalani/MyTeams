/*
** EPITECH PROJECT, 2021
** my_str_isalpha
** File description:
** isalpha
*/

int my_str_isalpha(char const *str)
{
    int a = 0;

    while (str[a] != '\0') {
        if ((str[a] < 'a' || str[a] > 'z') && (str[a] < 'A' || str[a] > 'Z'))
            return (0);
        a++;
    }
    return (1);
}
