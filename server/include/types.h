/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** types.h
*/

#ifndef TYPES_H_
    #define TYPES_H_

    #include <time.h>

typedef struct user_s {
    char *uuid;
    char *username;
} user_t;

typedef struct client_s {
    int fd;
    char *username;
    user_t *user;
} client_t;

typedef struct message_s {
    char *uuid;
    char *content;
    time_t time;
    user_t *user;
} message_t;

typedef struct thread_s {
    char *uuid;
    char *name;
} thread_t;

typedef struct channel_s {
    char *uuid;
    char *name;
    char *description;
    thread_t *threads;
} channel_t;

typedef struct team_s {
    char *uuid;
    char *name;
    char *description;
    channel_t *channels;
    user_t *users;
} team_t;

#endif
