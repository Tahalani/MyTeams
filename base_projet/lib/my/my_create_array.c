/*
** EPITECH PROJECT, 2022
** base_projet
** File description:
** my_create_array
*/

#include <stdlib.h>

char **my_malloc_tab(int nbr_rows)
{
    char **tab = malloc(sizeof(char *) * (nbr_rows + 1));

    tab[nbr_rows] = NULL;
    return (tab);
}
