/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** types.h
*/

#ifndef TYPES_H_
    #define TYPES_H_

    #include <bits/types/FILE.h>
    #include <sys/queue.h>
    #include <time.h>

    #define	linked_list(type)       \
    struct {                        \
        type *item;                 \
        SLIST_ENTRY(type) next;     \
    }

typedef struct user_s {
    char *uuid;
    char *username;
} user_t;

typedef linked_list(user_t) user_list_t;

typedef struct client_s {
    int fd;
    FILE *file;
    char *username;
    user_t *user;
} client_t;

typedef linked_list(client_t) client_list_t;

typedef struct message_s {
    char *uuid;
    char *content;
    time_t time;
    user_t *user;
} message_t;

typedef linked_list(message_t) message_list_t;

typedef struct thread_s {
    char *uuid;
    char *name;
    message_list_t messages;
} thread_t;

typedef linked_list(thread_t) thread_list_t;

typedef struct channel_s {
    char *uuid;
    char *name;
    char *description;
    thread_list_t threads;
} channel_t;

typedef linked_list(channel_t) channel_list_t;

typedef struct team_s {
    char *uuid;
    char *name;
    char *description;
    channel_list_t channels;
    user_list_t users;
} team_t;

typedef linked_list(team_t) team_list_t;

typedef struct data_s {
    user_list_t *users;
    team_list_t *teams;
    channel_list_t *channels;
    thread_list_t *threads;
    message_list_t *messages;
} data_t;

typedef struct server_s {
    int socket_fd;
    data_t *data;
    SLIST_HEAD(client_list, client_list_t) *clients;
} server_t;

#endif
