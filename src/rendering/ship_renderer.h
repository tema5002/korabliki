#pragma once

#include "../structs.h"
#include "window.h"
#include "../vector2d.h"

static void camera_follow(const window_t* w, const ship_t* ship, vector2d* offset, const vector2d* max) {
    float screen_x = ship->x - offset->x;
    float screen_y = ship->y - offset->y;

    float zone_x_min = w->size.x / 3.0f;
    float zone_x_max = w->size.x * 2.0f / 3.0f;
    float zone_y_min = w->size.y / 3.0f;
    float zone_y_max = w->size.y * 2.0f / 3.0f;

    if (screen_x < zone_x_min) {
        offset->x -= zone_x_min - screen_x;
    }
    else if (screen_x > zone_x_max) {
        offset->x += screen_x - zone_x_max;
    }

    if (screen_y < zone_y_min) {
        offset->y -= zone_y_min - screen_y;
    }
    else if (screen_y > zone_y_max) {
        offset->y += screen_y - zone_y_max;
    }

    if (w->size.x >= max->x) {
        offset->x = (max->x - w->size.x) / 2.0f;
    }
    else {
        offset->x = MAX(0, MIN(offset->x, max->x - w->size.x));
    }

    if (w->size.y >= max->y) {
        offset->y = (max->y - w->size.y) / 2.0f;
    }
    else {
        offset->y = MAX(0, MIN(offset->y, max->y - w->size.y));
    }
}

static void window_render_ship_base(
        const window_t* window,
        const float x,
        const float y,
        const vector2d* offset,
        const float angle,
        const float size
) {
    window_set_color(window, 255, 255, 0, 255);
    window_render_rotated_square(window, x - offset->x, y - offset->y, size, angle);
}

static void window_render_ship_direction(
        const window_t* window,
        const float x,
        const float y,
        const vector2d* offset,
        const float angle,
        const int thrust
) {
    if (thrust == -1) {
        window_set_color(window, 0, 0, 255, 255);
        window_render_arrow_angle(window, x - offset->x, y - offset->y, angle + -1 * SDL_PI_F, 30.0f);
    }
    else if (thrust == 1) {
        window_set_color(window, 255, 0, 0, 255);
        window_render_arrow_angle(window, x - offset->x, y - offset->y, angle, 30.0f);
    }
    else {
        window_set_color(window, 255, 255, 255, 255);
        window_render_arrow_angle(window, x - offset->x, y - offset->y, angle, 30.0f);
    }
}

static void window_render_ship_velocity(
        const window_t* window,
        const float x,
        const float y,
        const vector2d* offset,
        const float vx,
        const float vy
) {
    window_set_color(window, 0, 255, 0, 255);
    window_render_arrow(window, x - offset->x, y - offset->y, vx, vy);
}

static void window_render_ship_cooldown(const window_t* window, const ship_t* ship, const vector2d* offset) {
    if (ship->dash_cooldown < 0.0f) return;

    const float cooldown_ratio = 1.0f - ship->dash_cooldown / DASH_COOLDOWN;

    const float bar_width = ship->size;
    const float bar_height = 4.0f;

    const float x = ship->x - offset->x;
    const float y = ship->y - offset->y;

    window_set_color(window, 100, 100, 100, 150);
    window_render_rect(window, x - bar_width/2, y + ship->size/2 + 8, bar_width, bar_height);

    window_set_color(window, 0, 255, 255, 200);
    window_render_rect(window, x - bar_width/2, y + ship->size/2 + 8, bar_width * cooldown_ratio, bar_height);
}

static void window_render_ship_base_direction(
        const window_t* window,
        const float x,
        const float y,
        const vector2d* offset,
        const float size,
        const float angle,
        const int thrust
) {
    window_render_ship_base(window, x, y, offset, angle, size);
    window_render_ship_direction(window, x, y, offset, angle, thrust);
}

static void window_render_ship_full(const window_t* window, const ship_t* ship, const vector2d* offset) {
    window_render_ship_base(window, ship->x, ship->y, offset, ship->angle, ship->size);
    window_render_ship_direction(window, ship->x, ship->y, offset, ship->angle, ship->input_buffer.thrust);
    window_render_ship_velocity(window, ship->x, ship->y, offset, ship->vx, ship->vy);
    window_render_ship_cooldown(window, ship, offset);
}