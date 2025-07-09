#pragma once

#include "../shared/ship_net.h"
#include "window.h"

void window_render_ship_base(const window_t* window, const float x, const float y, const float angle, const float size);
void window_render_ship_direction(const window_t* window, const float x, const float y, const float angle, const int thrust);
void window_render_ship_velocity(const window_t* window, const float x, const float y, const float vx, const float vy);
void window_render_ship_cooldown(const window_t* window, const ship_t* ship);

static void __attribute__((unused)) window_render_ship_base_direction(const window_t* window, const float x, const float y, const float size, const float angle, const int thrust) {
    window_render_ship_base(window, x, y, angle, size);
    window_render_ship_direction(window, x, y, angle, thrust);
}

static void __attribute__((unused)) window_render_ship_full(const window_t* window, const ship_t* ship) {
    window_render_ship_base(window, ship->x, ship->y, ship->angle, ship->size);
    window_render_ship_direction(window, ship->x, ship->y, ship->angle, ship->input_buffer.thrust);
    window_render_ship_velocity(window, ship->x, ship->y, ship->vx, ship->vy);
    window_render_ship_cooldown(window, ship);
}