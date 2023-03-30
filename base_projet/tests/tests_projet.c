/*
** EPITECH PROJECT, 2021
** test
** File description:
** test units
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"
#include "projet.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout ();
    cr_redirect_stderr ();
}
