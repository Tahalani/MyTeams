/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** cache.c
*/

#include <stddef.h>

#include "server.h"
#include "types.h"

team_t *get_context_team(server_t *server, use_t *use)
{
    if (use->team_uuid == NULL) {
        return NULL;
    }
    if (use->team == NULL) {
        use->team = find_team_by_uuid(server, use->team_uuid);
    }
    return use->team;
}

channel_t *get_context_channel(server_t *server, use_t *use)
{
    if (use->channel_uuid == NULL) {
        return NULL;
    }
    if (use->channel == NULL) {
        use->channel = find_channel_by_uuid(server, use->channel_uuid);
    }
    return use->channel;
}

thread_t *get_context_thread(server_t *server, use_t *use)
{
    if (use->thread_uuid == NULL) {
        return NULL;
    }
    if (use->thread == NULL) {
        use->thread = find_thread_by_uuid(server, use->thread_uuid);
    }
    return use->thread;
}
