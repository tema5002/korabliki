#pragma once
#include "../map_state.h"
#include "../structs.h"
#include "memeq.h"

typedef struct server_client_t {
    ship_t ship;
    struct sockaddr_in socket;
    enum {
        SERVER_CLIENT_PLAYER,
        SERVER_CLIENT_CPU
    } type;
} server_client_t;

typedef struct server_state_t {
    server_client_t* clients;
    size_t clients_size;
    size_t max_clients;

    int sock;
    struct sockaddr_in server_addr;
    map_state_h map;
} server_state_t;

static server_client_t* find_server_client_by_addr(const server_state_t* state, const struct sockaddr_in* addr) {
    for (size_t i = 0; i < state->clients_size; i++) { if (
(sizeof(struct sockaddr_in) == 16) ?
        memeq16(&state->clients[i].socket, addr)
:
        memcmp(&state->clients[i].socket, addr, sizeof(struct sockaddr_in)) == 0

        ) {
            return &state->clients[i];
        }
    }
    return NULL;
}

static server_client_t* register_new_client(server_state_t* state) {
    if (state->clients_size >= state->max_clients) {
        return NULL;
    }
    server_client_t* c = &state->clients[state->clients_size];
    state->clients_size++;

    ship_t* ship = &c->ship;
    ship->x = state->map.width/8;
    ship->y = state->map.height/8;
    ship->vx = 0;
    ship->vy = 0;
    ship->angle = 0;
    ship->angular_velocity = 0;
    ship->size = 20.0f;
    ship->dash_timer = 0;
    ship->dash_cooldown = 0;
    ship->input_buffer.dash = 0;
    ship->input_buffer.rotate_left = 0;
    ship->input_buffer.rotate_right = 0;
    ship->input_buffer.thrust = 0;
    ship->ping = 0;

    return c;
}

static server_client_t* register_new_cpu(server_state_t* state) {
    server_client_t* client = register_new_client(state);
    if (client == NULL) {
        return NULL;
    }
    memcpy(client->ship.name, "CPU", strlen("CPU") + 1);
    client->type = SERVER_CLIENT_CPU;
    return client;
}

static server_client_t* register_new_player(server_state_t* state, const client_join_request_t* packet, const struct sockaddr_in* addr) {
    server_client_t* client = register_new_client(state);
    if (client == NULL) {
        return NULL;
    }
    client->type = SERVER_CLIENT_PLAYER;
    client->socket = *addr;
    ship_t* ship = &client->ship;
    memcpy(ship->name, packet->name, MAX_NICK_LEN);
    ship->ping = INFINITY;
    return client;
}