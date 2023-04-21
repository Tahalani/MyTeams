/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** loading
*/

#include <sys/stat.h>

#include "database.h"
#include "types.h"

void load_data(server_t *server)
{
    load_users(server);
    load_teams(server);
    load_channels(server);
    load_threads(server);
    load_messages(server);
    load_team_user_relations(server);
    load_team_channel_relations(server);
    load_channel_thread_relations(server);
}

void save_data(server_t *server)
{
    mkdir("server/database/", 0777);
    save_users(server);
    save_teams(server);
    save_channels(server);
    save_threads(server);
    save_messages(server);
    save_team_user_relations(server);
    save_team_channel_relations(server);
    save_channel_thread_relations(server);
}
