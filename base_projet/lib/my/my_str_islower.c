/*
** EPITECH PROJECT, 2021
** my_str_islower
** File description:
** islower
*/

int my_str_islower(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 65 && str[i] <= 90)
            return (0);
    }
    return (1);
}
