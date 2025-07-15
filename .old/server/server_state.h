#pragma once

#include <netinet/in.h>
#include "../shared/ship_net.h"

typedef struct server_state_t {
    ship_t ships[MAX_PLAYERS];
    struct sockaddr_in addrs[MAX_PLAYERS];
    float server_time;
    float tick_delta;
    float width;
    float height;
    int sock;
    struct sockaddr_in server_addr;
} server_state_t;

ship_t* find_player_by_addr(server_state_t* state, const struct sockaddr_in* addr);
int register_new_player(server_state_t* state, const register_packet_t* packet, const struct sockaddr_in* addr);
