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

Test(get_arguments, get_arguments)
{
    char *input = strdup("create \"server_test\" \"Hello World\"");
    char **args = get_arguments(input);

    cr_assert_str_eq(args[0], "server_test");
    cr_assert_str_eq(args[1], "Hello World");
    cr_assert_eq(args[2], NULL);
    free_array(args);
    free(input);
}
