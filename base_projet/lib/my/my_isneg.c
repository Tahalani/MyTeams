/*
** EPITECH PROJECT, 2021
** My_isneg
** File description:
** Affiche N si le nombre est inferieur à 0 et P si superieur a 0.
*/

void my_putchar(char c);

int my_isneg(int n)
{
    if (n < 0)
        my_putchar('N');
    else
        my_putchar('P');
    return (0);
}
