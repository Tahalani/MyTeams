/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** test_utils.c
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include "cli.h"
#include "types.h"

Test(is_uuid, is_uuid)
{
    char *uuid = strdup("12345678-1234-1234-1234-123456789012");
    char *not_uuid = strdup("12345678-1234-1234-1234-12345678901");

    cr_assert(is_uuid(uuid));
    cr_assert(!is_uuid(not_uuid));
    free(uuid);
    free(not_uuid);
}

Test(str_to_word, str_to_word)
{
    char *str = strdup("Hello World");
    char **words = str_to_word(str, ' ');

    cr_assert_str_eq(words[0], "Hello");
    cr_assert_str_eq(words[1], "World");
    cr_assert_eq(words[2], NULL);
    free_array(words);
    free(str);
}

Test(array_len, array_len)
{
    char *str = strdup("Hello World");
    char **words = str_to_word(str, ' ');

    cr_assert_eq(array_len(words), 2);
    free_array(words);
    free(str);
}