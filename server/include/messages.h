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
        "500 Unknown command.",
        "530 Please login with /login.",
        "400 Please add a valid argument.",
        NULL,
};

#endif
