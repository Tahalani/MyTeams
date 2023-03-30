/*
** EPITECH PROJECT, 2021
** len_cmp
** File description:
** len compare
*/

int my_strlen(char const *str);

int len_cmp(char *str1, char *str2)
{
    if (my_strlen(str1) > my_strlen(str2))
        return (1);
    return (0);
}
