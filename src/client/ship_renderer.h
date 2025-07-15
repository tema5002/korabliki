#pragma once

#include "../structs.h"
#include "../window.h"

static void window_render_ship_base(const window_t* window, const float x, const float y, const float angle, const float size) {
    window_set_color(window, 255, 255, 0, 255);
    window_render_rotated_square(window, x, y, size, angle);
}

static void window_render_ship_direction(const window_t* window, const float x, const float y, const float angle, const int thrust) {
    if (thrust == -1) {
        window_set_color(window, 0, 0, 255, 255);
        window_render_arrow_angle(window, x, y, angle + -1 * SDL_PI_F, 30.0f);
    }
    else if (thrust == 1) {
        window_set_color(window, 255, 0, 0, 255);
        window_render_arrow_angle(window, x, y, angle, 30.0f);
    }
    else {
        window_set_color(window, 255, 255, 255, 255);
        window_render_arrow_angle(window, x, y, angle, 30.0f);
    }
}

static void window_render_ship_velocity(const window_t* window, const float x, const float y, const float vx, const float vy) {
    window_set_color(window, 0, 255, 0, 255);
    window_render_arrow(window, x, y, vx, vy);
}

static void window_render_ship_cooldown(const window_t* window, const ship_t* ship) {
    if (ship->dash_cooldown < 0.0f) return;

    const float cooldown_ratio = 1.0f - ship->dash_cooldown / DASH_COOLDOWN;

    const float bar_width = ship->size;
    const float bar_height = 4.0f;

    window_set_color(window, 100, 100, 100, 150);
    window_render_rect(window, ship->x - bar_width/2, ship->y + ship->size/2 + 8, bar_width, bar_height);

    window_set_color(window, 0, 255, 255, 200);
    window_render_rect(window, ship->x - bar_width/2, ship->y + ship->size/2 + 8, bar_width * cooldown_ratio, bar_height);
}

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
