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

typedef struct uuid_s {
    char *uuid;
    SLIST_ENTRY(uuid_s) next;
} uuid_t;

typedef struct user_s {
    char *uuid;
    char *username;
    SLIST_HEAD(team_l, uuid_s) *teams;
    SLIST_ENTRY(user_s) next;
} user_t;

typedef struct thread_s {
    char *uuid;
    char *name;
    char *message;
    char *author;
    time_t created_at;
    SLIST_HEAD(message_l, uuid_s) *messages;
    SLIST_ENTRY(thread_s) next;
} thread_t;

typedef struct channel_s {
    char *uuid;
    char *name;
    char *description;
    SLIST_HEAD(thread_l, uuid_s) *threads;
    SLIST_ENTRY(channel_s) next;
} channel_t;

typedef struct team_s {
    char *uuid;
    char *name;
    char *description;
    SLIST_HEAD(, uuid_s) *channels;
    SLIST_HEAD(user_l, uuid_s) *users;
    SLIST_ENTRY(team_s) next;
} team_t;

typedef struct use_s {
    team_t *team;
    char *team_uuid;
    channel_t *channel;
    char *channel_uuid;
    thread_t *thread;
    char *thread_uuid;
    int use_level;
} use_t;

typedef struct client_s {
    int fd;
    FILE *file;
    user_t *user;
    use_t *use;
    SLIST_ENTRY(client_s) next;
} client_t;

typedef struct message_s {
    char *uuid;
    char *body;
    char *author;
    char *target;
    time_t created_at;
    bool is_private;
    SLIST_ENTRY(message_s) next;
} message_t;

typedef struct data_s {
    SLIST_HEAD(user_list, user_s) *users;
    SLIST_HEAD(team_list, team_s) *teams;
    SLIST_HEAD(channel_list, channel_s) *channels;
    SLIST_HEAD(thread_list, thread_s) *threads;
    SLIST_HEAD(message_list, message_s) *messages;
} data_t;

typedef struct server_s {
    int socket_fd;
    data_t *data;
    SLIST_HEAD(client_list, client_s) *clients;
} server_t;

#endif
