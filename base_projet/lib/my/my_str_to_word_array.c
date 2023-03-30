/*
** EPITECH PROJECT, 2022
** str_to_word_array
** File description:
** str to word array
*/

#include <stdlib.h>

int my_str_compt(char a, char separator)
{
    if (a == separator || a == '\0') {
        return (0);
    }
    return (1);
}

int compteur_word(char const *str, char separator)
{
    int j = 0;
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (my_str_compt(str[i], separator) == 1 &&
        my_str_compt(str[i + 1], separator) == 0)
            j++;
    }
    if (str[0] != '\0' && j == 0 && str[0] != separator)
        j++;
    return (j);
}

char **mal_char(char const *str, char separator)
{
    int x = 0;
    int a = 0;
    int i = 0;
    char **pl = malloc(sizeof(char *) * (compteur_word(str, separator) + 1));
    int count = compteur_word(str, separator);

    for (; my_str_compt(str[i], separator) == 0; i++);
    for (; x != count; i++, a++) {
        if (my_str_compt(str[i], separator) == 0) {
            pl[x] = malloc(sizeof(char) * (a + 1));
            a = 0;
            x++;
        }
        for (; str[i] == separator; i++);
    }
    if (my_str_compt(str[i - 1], separator) != 0) {
        pl[count - 1] = malloc(sizeof(char) * (a + 1));
    }
    return (pl);
}

char **my_str_to_word_array(char const *str, char separator)
{
    char **tab = mal_char(str, separator);
    int y = 0;
    int i = 0;

    for (; my_str_compt(str[i], separator) == 0; i++);
    for (int x = 0; y != compteur_word(str, separator); y++) {
        while (my_str_compt(str[i], separator) == 1) {
            tab[y][x] = str[i];
            x++;
            i++;
        }
        for (; str[i] == separator; i++);
        tab[y][x] = '\0';
        x = 0;
    }
    tab[y] = NULL;
    return (tab);
}
