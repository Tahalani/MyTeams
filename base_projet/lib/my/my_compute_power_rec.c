/*
** EPITECH PROJECT, 2021
** my_compute_power_rec
** File description:
** return with raised to the power p
*/

int my_compute_power_rec(int nb, int p)
{
    int a = 0;

    if (p == 0)
        return (1);
    if (p < 0)
        return (0);
    a = nb * my_compute_power_rec(nb, p - 1);
    return (a);
}
