#pragma once
#include <SDL3/SDL_rect.h>

typedef struct client_state_t {
    ship_t* ships;
    size_t max_ships_size;
    size_t ships_size;
    uint64_t last_ping_time;
    int sock;
    struct sockaddr_in server_addr;
    map_state_h map;
} client_state_t;