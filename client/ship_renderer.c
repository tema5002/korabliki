#include "ship_renderer.h"

void window_render_ship_base(const window_t* window, const float x, const float y, const float angle, const float size) {
    window_set_color(window, 255, 255, 0, 255);
    window_render_rotated_square(window, x, y, size, angle);
}

void window_render_ship_direction(const window_t* window, const float x, const float y, const float angle, const int thrust) {
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

void window_render_ship_velocity(const window_t* window, const float x, const float y, const float vx, const float vy) {
    window_set_color(window, 0, 255, 0, 255);
    window_render_arrow(window, x, y, vx, vy);
}

void window_render_ship_cooldown(const window_t* window, const ship_t* ship) {
    if (ship->dash_cooldown < 0.0f) return;

    const float cooldown_ratio = 1.0f - ship->dash_cooldown / DASH_COOLDOWN;

    const float bar_width = ship->size;
    const float bar_height = 4.0f;

    window_set_color(window, 100, 100, 100, 150);
    window_render_rect(window, ship->x - bar_width/2, ship->y + ship->size/2 + 8, bar_width, bar_height);

    window_set_color(window, 0, 255, 255, 200);
    window_render_rect(window, ship->x - bar_width/2, ship->y + ship->size/2 + 8, bar_width * cooldown_ratio, bar_height);
}