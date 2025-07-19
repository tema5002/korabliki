#pragma once
#include "ui_window.h"

static void ui_window_make_local_game(ui_window_t* ui_window, const float scale) {
    Clay_BeginLayout();
    ui_window->array = Clay_EndLayout();
}

static void ui_window_render_local_game(ui_window_t* ui_window) {
    ship_t* ship = &ui_window->value.local_data.ship;
    vector2d* offset = &ui_window->value.local_data.offset;
    vector2d* max = &ui_window->value.local_data.map.size;

    const bool* keys = SDL_GetKeyboardState(NULL);
    ship->input_buffer.thrust = 0;
    if (keys[SDL_SCANCODE_W]) {
        ship->input_buffer.thrust = 1;
    }
    else if (keys[SDL_SCANCODE_S]) {
        ship->input_buffer.thrust = -1;
    }

    ship->input_buffer.rotate_left = keys[SDL_SCANCODE_A];
    ship->input_buffer.rotate_right = keys[SDL_SCANCODE_D];
    ship->input_buffer.dash = keys[SDL_SCANCODE_SPACE];

    if (keys[SDL_SCANCODE_ESCAPE]) {
        ui_window_switch_to_main_menu(ui_window);
        return;
    }

    update_ship(ship, 1.0f/60, *max);
    camera_follow(ui_window->window, ship, offset, max);

    window_set_color(ui_window->window, 0, 0, 0, 255);
    window_clear(ui_window->window);
    int tile_size = 64;
    int ox = ((int)offset->x) % tile_size;
    int oy = ((int)offset->y) % tile_size;

    for (int x = -tile_size; x < ui_window->window->size.x + tile_size; x += tile_size) {
        for (int y = -tile_size; y < ui_window->window->size.y + tile_size; y += tile_size) {
            int tx = (x + offset->x) / tile_size;
            int ty = (y + offset->y) / tile_size;

            bool is_dark = (tx % 2 == ty % 2);
            uint8_t val = is_dark ? 16 : 64;

            window_set_color(ui_window->window, val, val, val, 255);
            window_render_fill_rect(ui_window->window, x - ox, y - oy, tile_size, tile_size);
        }
    }

    window_render_ship_full(ui_window->window, ship, offset);
    //k_font_render_centered(ui_window->window, ship->name, ship->x - offset->x, ship->y + ship->size - offset->y, 1);
}