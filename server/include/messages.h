/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** messages.h
*/

#ifndef MESSAGES_H_
    #define MESSAGES_H_

    #include <stddef.h>

static const char *MESSAGES[11] = {
        "200 Command okay.",
        "220 Service ready for new user.",
        "400 Invalid number of arguments.",
        "410 User not found.",
        "420 Username too long.",
        "500 Unknown command.",
        "530 Please login with /login.",
        "570 Team not found.",
        "580 Channel not found.",
        "590 Thread not found.",
        NULL,
};

#endif
