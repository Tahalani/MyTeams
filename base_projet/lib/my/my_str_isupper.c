/*
** EPITECH PROJECT, 2021
** my_str_isupper
** File description:
** isupper
*/

int my_str_isupper(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            return (0);
    }
    return (1);
}
