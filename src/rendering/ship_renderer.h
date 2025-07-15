#pragma once

#include "../structs.h"
#include "window.h"
#include "../vector2d.h"

typedef struct ship_window_t {
    window_t* window;
    vector2d max;
    ship_t* main_ship;
    vector2d offset;
    SDL_FRect dead_zone;
} ship_window_t;

static void camera_follow(ship_window_t* w) {
    int window_w = 0, window_h = 0;
    SDL_GetWindowSizeInPixels(w->window->window, &window_w, &window_h);

    vector2d offset = w->offset;
    float ship_x = w->main_ship->x;
    float ship_y = w->main_ship->y;

    float screen_x = ship_x - offset.x;
    float screen_y = ship_y - offset.y;

    float zone_x_min = window_w / 3.0f;
    float zone_x_max = window_w * 2.0f / 3.0f;
    float zone_y_min = window_h / 3.0f;
    float zone_y_max = window_h * 2.0f / 3.0f;

    if (screen_x < zone_x_min) {
        offset.x -= zone_x_min - screen_x;
    }
    else if (screen_x > zone_x_max) {
        offset.x += screen_x - zone_x_max;
    }

    if (screen_y < zone_y_min) {
        offset.y -= zone_y_min - screen_y;
    }
    else if (screen_y > zone_y_max) {
        offset.y += screen_y - zone_y_max;
    }

    if (window_w >= w->max.x) {
        offset.x = (w->max.x - window_w) / 2.0f;
    }
    else {
        offset.x = MAX(0, MIN(offset.x, w->max.x - window_w));
    }

    if (window_h >= w->max.y) {
        offset.y = (w->max.y - window_h) / 2.0f;
    }
    else {
        offset.y = MAX(0, MIN(offset.y, w->max.y - window_h));
    }

    w->offset = offset;
}


static void window_render_ship_base(const ship_window_t* window, const float x, const float y, const float angle, const float size) {
    window_set_color(window->window, 255, 255, 0, 255);
    window_render_rotated_square(window->window, x - window->offset.x, y - window->offset.y, size, angle);
}

static void window_render_ship_direction(const ship_window_t* window, const float x, const float y, const float angle, const int thrust) {
    if (thrust == -1) {
        window_set_color(window->window, 0, 0, 255, 255);
        window_render_arrow_angle(window->window, x - window->offset.x, y - window->offset.y, angle + -1 * SDL_PI_F, 30.0f);
    }
    else if (thrust == 1) {
        window_set_color(window->window, 255, 0, 0, 255);
        window_render_arrow_angle(window->window, x - window->offset.x, y - window->offset.y, angle, 30.0f);
    }
    else {
        window_set_color(window->window, 255, 255, 255, 255);
        window_render_arrow_angle(window->window, x - window->offset.x, y - window->offset.y, angle, 30.0f);
    }
}

static void window_render_ship_velocity(const ship_window_t* window, const float x, const float y, const float vx, const float vy) {
    window_set_color(window->window, 0, 255, 0, 255);
    window_render_arrow(window->window, x - window->offset.x, y - window->offset.y, vx, vy);
}

static void window_render_ship_cooldown(const ship_window_t* window, const ship_t* ship) {
    if (ship->dash_cooldown < 0.0f) return;

    const float cooldown_ratio = 1.0f - ship->dash_cooldown / DASH_COOLDOWN;

    const float bar_width = ship->size;
    const float bar_height = 4.0f;

    const float x = ship->x - window->offset.x;
    const float y = ship->y - window->offset.y;
    
    window_set_color(window->window, 100, 100, 100, 150);
    window_render_rect(window->window, x - bar_width/2, y + ship->size/2 + 8, bar_width, bar_height);

    window_set_color(window->window, 0, 255, 255, 200);
    window_render_rect(window->window, x - bar_width/2, y + ship->size/2 + 8, bar_width * cooldown_ratio, bar_height);
}

static void window_render_ship_base_direction(const ship_window_t* window, const float x, const float y, const float size, const float angle, const int thrust) {
    window_render_ship_base(window, x, y, angle, size);
    window_render_ship_direction(window, x, y, angle, thrust);
}

static void window_render_ship_full(const ship_window_t* window, const ship_t* ship) {
    window_render_ship_base(window, ship->x, ship->y, ship->angle, ship->size);
    window_render_ship_direction(window, ship->x, ship->y, ship->angle, ship->input_buffer.thrust);
    window_render_ship_velocity(window, ship->x, ship->y, ship->vx, ship->vy);
    window_render_ship_cooldown(window, ship);
}
