/*
** EPITECH PROJECT, 2021
** my_strcat
** File description:
** my_strcat
*/

#include <stddef.h>
#include <stdlib.h>

int my_strlen(char const *str);

char *my_strcat(char *dest, char const *src)
{
    int one = 0;
    int two = 0;

    for (; dest[one] != '\0'; one++);
    while (src[two] != '\0') {
        dest[one + two] = src[two];
        two++;
    }
    dest[one + two] = '\0';
    return (dest);
}

char *my_strconcat(char *dest, char const *src)
{
    int one = my_strlen(dest);
    int two = my_strlen(src);
    char *result = malloc(sizeof(char) * (one + two + 1));
    int i = 0;
    int j = 0;

    if (result == NULL)
        return (NULL);
    for (; dest[i] != '\0'; i++) {
        result[i] = dest[i];
    }
    for (; src[j] != '\0'; j++, i++)
        result[i] = src[j];
    result[i] = '\0';
    return (result);
}
