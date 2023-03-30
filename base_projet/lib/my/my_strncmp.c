/*
** EPITECH PROJECT, 2021
** my_strncmp
** File description:
** my_strncmp
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while ((s1[i] != '\0' && s2[i] != '\0') && i < n) {
        if (s1[i] == '\0' && s2[i] != '\0')
            return (1);
        if (s2[i] == '\0' && s1[i] != '\0')
            return (1);
        if (s1[i] != s2[i])
            return (1);
        i++;
    }
    return (0);
}
