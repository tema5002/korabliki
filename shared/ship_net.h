#pragma once
#include <stdbool.h>
#include <stdint.h>

#define MAX_NICK_LEN 28
#define MAX_PLAYERS 4
#define DASH_COOLDOWN 0.5f

typedef struct ship_input_packet_t {
    int8_t thrust;
    bool rotate_left;
    bool rotate_right;
    bool dash;
} __attribute__((packed)) ship_input_packet_t;

typedef struct ship_t {
    float x, y;
    float vx, vy;
    float angle;
    float angular_velocity;
    float size;
    float dash_timer;
    float dash_cooldown;
    char name[MAX_NICK_LEN];
    uint8_t color_r, color_g, color_b;
    bool connected;
    ship_input_packet_t input_buffer;
    float ping;
} __attribute__((packed)) ship_t;

typedef struct register_packet_t {
    char name[MAX_NICK_LEN];
    uint8_t color_r, color_g, color_b;
} __attribute__((packed)) register_packet_t;

typedef struct registered_packet_t {
    int width;
    int height;
    int id;
} __attribute__((packed)) registered_packet_t;
