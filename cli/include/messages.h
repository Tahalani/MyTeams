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
};

#endif
