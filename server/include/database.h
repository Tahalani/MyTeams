/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** database.h
*/

#ifndef DATABASE_H_
    #define DATABASE_H_

    #include "constants.h"
    #include "types.h"

    #define DB_FILE_USERS "server/database/users"
    #define DB_FILE_TEAMS "server/database/teams"
    #define DB_FILE_CHANNELS "server/database/channels"
    #define DB_FILE_THREADS "server/database/threads"
    #define DB_FILE_MESSAGES "server/database/messages"

typedef struct PACKED relation_s {
    char first_uuid[UUID_LENGTH + 1];
    char second_uuid[UUID_LENGTH + 1];
} relation_t;

typedef struct parsed_user_s {
    char uuid[UUID_LENGTH + 1];
    char username[MAX_NAME_LENGTH + 1];
} parsed_user_t;

typedef struct parsed_team_s {
    char uuid[UUID_LENGTH + 1];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
} parsed_team_t;

typedef struct parsed_channel_s {
    char uuid[UUID_LENGTH + 1];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
} parsed_channel_t;

typedef struct parsed_thread_s {
    char uuid[UUID_LENGTH + 1];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
} parsed_thread_t;

typedef struct parsed_message_s {
    char uuid[UUID_LENGTH + 1];
    char body[MAX_BODY_LENGTH + 1];
    char uuid_user[UUID_LENGTH + 1];
} parsed_message_t;

void save_user(user_t *user, int fd);
void save_team(team_t *team, int fd);
void save_channel(channel_t *channel, int fd);
void save_thread(thread_t *thread, int fd);
void save_data(server_t *server);
void save_message(message_t *message, int fd);

void relation_team_user(server_t *server, int fd);
void relation_channel_team(server_t *server, int fd);
void relation_thread_channel(server_t *server, int fd);
void relation_message_thread(server_t *server, int fd);

void load_relation_team_user(server_t *server, int fd);
void load_relation_channel_team(server_t *server, int fd);
void load_relation_thread_channel(server_t *server, int fd);
void load_relation_message_thread(server_t *server, int fd);

relation_t *load_relation(int fd);

void load_users(server_t *server);
void load_teams(server_t *server);
void load_channels(server_t *server);
void load_threads(server_t *server);
void load_messages(server_t *server);

#endif
