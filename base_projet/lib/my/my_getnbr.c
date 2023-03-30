/*
** EPITECH PROJECT, 2021
** my_getnbr
** File description:
** my_getnbr
*/

int my_getnbr(char *str)
{
    int nbr = 0;
    int i = 0;
    int j = 1;

    for (; str[i] == '+' || str[i] == '-'; i++) {
        if (str[i] == '-')
            j *= -1;
    }
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            nbr *= 10;
            nbr = nbr + str[i] - '0';
            i++;
        } else
            return (nbr * j);
        }
    return (nbr * j);
}
