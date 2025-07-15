#pragma once
#include <stdbool.h>
#include <stdint.h>

#define MAX_NICK_LEN 28
#define DASH_COOLDOWN 0.5f

typedef struct client_input_request_t {
    int8_t thrust;
    bool rotate_left;
    bool rotate_right;
    bool dash;
} __attribute__((packed)) client_input_request_t;

typedef struct ship_t {
    float x, y;
    float vx, vy;
    float angle;
    float angular_velocity;
    float size;
    float dash_timer;
    float dash_cooldown;
    char name[MAX_NICK_LEN];
    client_input_request_t input_buffer;
    float ping;
} __attribute__((packed)) ship_t;

typedef struct registered_packet_t {
    map_state_h map;
} __attribute__((packed)) registered_packet_t;

#define CLIENT_REQUEST_MAX_SIZE (\
    1 + /* packet type */ \
    MAX3(\
        sizeof(client_join_request_t), \
        sizeof(client_input_request_t), \
        sizeof(client_chat_request_t) \
    )\
)

enum {
    CLIENT_REQUEST_JOIN = 0,
    CLIENT_REQUEST_INPUT = 1,
    CLIENT_REQUEST_CHAT = 2,
    CLIENT_REQUEST_PING = 3
};

enum {
    SERVER_REQUEST_JOIN = 0,
    SERVER_REQUEST_SERVER_FULL = 1,
    SERVER_REQUEST_SHIPS = 2
};

typedef struct server_join_request_t {
    map_state_h map;
    size_t max_ships_size;
} server_join_request_t;

typedef struct client_join_request_t {
    char name[MAX_NICK_LEN];
} client_join_request_t;

typedef struct client_chat_request_t {
    char message[255];
    uint8_t size;
} client_chat_request_t;
