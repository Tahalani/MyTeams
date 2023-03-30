/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** messages.h
*/

#ifndef MESSAGES_H_
    #define MESSAGES_H_

    #include <stddef.h>

static const char *MESSAGES[6] = {
        "200 Command okay.",
        "220 Service ready for new user.",
        "400 Invalid number of arguments.",
        "500 Unknown command.",
        "530 Please login with /login.",
        NULL,
};

#endif
