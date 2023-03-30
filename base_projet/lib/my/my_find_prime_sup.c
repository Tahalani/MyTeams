/*
** EPITECH PROJECT, 2021
** my_find_prime_sup
** File description:
** return the smallest prime number
*/

int my_is_prime(int nb);

int my_find_prime_sup(int nb)
{
    for (; my_is_prime(nb) != 1; nb++);
    return (nb);
}
