#include "server_state.h"

#include <string.h>
#include <math.h>

ship_t* find_player_by_addr(server_state_t* state, const struct sockaddr_in* addr) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (memcmp(&state->addrs[i], addr, sizeof(struct sockaddr_in)) == 0) {
            return &state->ships[i];
        }
    }
    return NULL;
}

int register_new_player(server_state_t* state, const register_packet_t* packet, const struct sockaddr_in* addr) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!state->ships[i].connected) {
            state->ships[i].x = state->width/2;
            state->ships[i].y = state->height/2;
            state->ships[i].vx = 0;
            state->ships[i].vy = 0;
            state->ships[i].angle = 0;
            state->ships[i].angular_velocity = 0;
            state->ships[i].size = 20.0f;
            state->ships[i].dash_timer = 0;
            state->ships[i].dash_cooldown = 0;
            memcpy(state->ships[i].name, packet->name, MAX_NICK_LEN);
            state->ships[i].color_r = 255;
            state->ships[i].color_g = 255;
            state->ships[i].color_b = 0;
            state->ships[i].connected = 1;
            state->ships[i].input_buffer.dash = 0;
            state->ships[i].input_buffer.rotate_left = 0;
            state->ships[i].input_buffer.rotate_right = 0;
            state->ships[i].input_buffer.thrust = 0;
            state->ships[i].ping = 0;

            state->addrs[i] = *addr;
            return i;
        }
    }
    return -1;
}