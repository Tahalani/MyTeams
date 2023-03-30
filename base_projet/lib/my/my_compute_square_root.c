/*
** EPITECH PROJECT, 2021
** my_compute_square_root
** File description:
** my_compute_square_root
*/

int my_compute_square_root(int nb)
{
    int i = 1;
    int result = 0;

    if (nb <= 0)
        return (0);
    for (;result != nb; i++) {
        result = i * i;
        if (result > nb)
            return (0);
    }
    return (i - 1);
}
