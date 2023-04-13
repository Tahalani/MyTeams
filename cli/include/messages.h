/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** messages.h
*/

#ifndef MESSAGES_H_
    #define MESSAGES_H_

    #include <stddef.h>

    #define MESSAGES_COUNT (sizeof(MESSAGES) / sizeof(message_t))

typedef struct message_s {
    int code;
    const char *message;
} message_t;

static const message_t MESSAGES[] = {
        { 200, "Command okay." },
        { 220, "Service ready for new user." },
        { 400, "Invalid number of arguments." },
        { 401, "Invalid format of arguments." },
        { 404, "Unknown command." },
        { 420, "Argument must be a UUID." },
        { 421, "Too long username." },
        { 430, "Please login with /login." },
        { 440, "Unknown team." },
        { 441, "Unknown channel." },
        { 442, "Unknown thread." },
        { 500, "An internal error occured." },
};

#endif
