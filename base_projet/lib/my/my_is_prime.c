/*
** EPITECH PROJECT, 2021
** my_is_prime
** File description:
** return 1 if nb is prime and 0 if not
*/

int my_is_prime(int nb)
{
    int i = 2;

    if (nb <= 1)
        return (0);
    while (i < nb) {
        if (nb / i * i == nb)
            i++;
        return (0);
    }
    return (1);
}
