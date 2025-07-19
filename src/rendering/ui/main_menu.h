#pragma once

#include "ui_window.h"
#include "../ship_renderer.h"

char* main_menu_status = "";

static void main_menu_hover_handler(Clay_ElementId id, Clay_PointerData pd, intptr_t userdata) {
    if (id.id == CLAY_ID("MainMenuLocalButton").id) {
        main_menu_status = "Play a singleplayer game";
    }
    else if (id.id == CLAY_ID("MainMenuMultiplayerButton").id) {
        main_menu_status = "Play on the local network or over the internet";
    }
    else if (id.id == CLAY_ID("MainMenuSettingsButton").id) {
        main_menu_status = "Change language, volume, etc.";
    }
    else if (id.id == CLAY_ID("MainMenuExitButton").id) {
        main_menu_status = "Exit back to the real world";
    }
    else if (id.id == CLAY_ID("MainMenuTitle").id) {
        main_menu_status = "korabliki v0.0.1";
    }

    if (pd.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        if (id.id == CLAY_ID("MainMenuExitButton").id) {
            exit(EXIT_SUCCESS);
        }

        if (id.id == CLAY_ID("MainMenuLocalButton").id) {
            ui_window_switch_to_local_game((ui_window_t*)userdata);
        }
    }
}

static void ui_window_make_main_menu(ui_window_t* ui_window, const float scale) {
    Clay_BeginLayout();

    CLAY({
        .id = CLAY_ID("MainMenuVerticalStack"),
        .layout = {
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(1) },
            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
            .padding = CLAY_PADDING_ALL(16),
        },
        .backgroundColor = { 0 }
    }) {
        CLAY({
            .id = CLAY_ID("MainMenuContainer"),
            .layout = {
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .sizing = { CLAY_SIZING_GROW(1), CLAY_SIZING_GROW(1) },
                .padding = CLAY_PADDING_ALL(32),
                .childGap = 12 * scale,
                .childAlignment = { .x = CLAY_ALIGN_X_CENTER }
            },
            .backgroundColor = { 0 }
        }) {
            CLAY({
                .id = CLAY_ID("MainMenuTitle"),
                .layout = {
                    .sizing = { .width = CLAY_SIZING_FIXED(100 * scale), .height = CLAY_SIZING_FIXED(25 * scale) },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER }
                },
                .backgroundColor = { 0 }
            }) {
                Clay_OnHover(main_menu_hover_handler, (uintptr_t)ui_window);

                CLAY_TEXT(CLAY_STRING("korabliki"), CLAY_TEXT_CONFIG({
                    .fontSize = 2 * scale,
                    .textColor = {255, 255, 255, 255},
                    .textAlignment = CLAY_TEXT_ALIGN_CENTER
                }));
            }

            Clay_OnHover(main_menu_hover_handler, 0);
            CLAY({
                .id = CLAY_ID("MainMenuLocalButton"),
                .layout = {
                    .sizing = { .width = CLAY_SIZING_FIXED(100 * scale), .height = CLAY_SIZING_FIXED(25 * scale) },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER }
                },
                .backgroundColor = Clay_Hovered() ? (Clay_Color){ 100, 100, 255, 255 } : (Clay_Color){ 100, 100, 100, 255 }
                }
            ) {
                Clay_OnHover(main_menu_hover_handler, (uintptr_t)ui_window);

                CLAY_TEXT(CLAY_STRING("Local game"), CLAY_TEXT_CONFIG({
                    .fontSize = 1 * scale,
                    .textColor = {255, 255, 255, 255},
                    .textAlignment = CLAY_TEXT_ALIGN_CENTER
                }));
            }

            CLAY({
                .id = CLAY_ID("MainMenuMultiplayerButton"),
                .layout = {
                    .sizing = { .width = CLAY_SIZING_FIXED(100 * scale), .height = CLAY_SIZING_FIXED(25 * scale) },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER }
                },
                .backgroundColor = Clay_Hovered() ? (Clay_Color){ 100, 100, 255, 255 } : (Clay_Color){ 100, 100, 100, 255 }
            }) {
                Clay_OnHover(main_menu_hover_handler, (uintptr_t)ui_window);

                CLAY_TEXT(CLAY_STRING("Multiplayer"), CLAY_TEXT_CONFIG({
                    .fontSize = 1 * scale,
                    .textColor = {255, 255, 255, 255},
                    .textAlignment = CLAY_TEXT_ALIGN_CENTER
                }));
            }

            CLAY({
                .id = CLAY_ID("MainMenuSettingsButton"),
                .layout = {
                    .sizing = { .width = CLAY_SIZING_FIXED(100 * scale), .height = CLAY_SIZING_FIXED(25 * scale) },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER }
                },
                .backgroundColor = Clay_Hovered() ? (Clay_Color){ 100, 100, 255, 255 } : (Clay_Color){ 100, 100, 100, 255 }
            }) {
                Clay_OnHover(main_menu_hover_handler, 0);

                CLAY_TEXT(CLAY_STRING("Settings"), CLAY_TEXT_CONFIG({
                    .fontSize = 1 * scale,
                    .textColor = {255, 255, 255, 255},
                    .textAlignment = CLAY_TEXT_ALIGN_CENTER
                }));
            }
        }

        CLAY({
            .layout = {
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(1) }
            }
        }) {}

        CLAY({
            .id = CLAY_ID("MainMenuBottomPanel"),
            .layout = {
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIT(0) },
                .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                .padding = CLAY_PADDING_ALL(16),
            },
            .backgroundColor = { 0 }
        }) {
            CLAY_TEXT(((Clay_String) {
                .isStaticallyAllocated = false,
                .chars = main_menu_status,
                .length = strlen(main_menu_status)
            }), CLAY_TEXT_CONFIG({
                .fontSize = 1 * scale,
                .textColor = {255, 255, 255, 255},
                .textAlignment = CLAY_TEXT_ALIGN_CENTER
            }));

            CLAY({
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(1), CLAY_SIZING_GROW(0) }
                }
            });

            CLAY({
                .id = CLAY_ID("MainMenuExitButton"),
                .layout = {
                    .sizing = {
                        .width = CLAY_SIZING_FIXED(80 * scale),
                        .height = CLAY_SIZING_FIXED(25 * scale)
                    },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                },
                .backgroundColor = Clay_PointerOver(CLAY_ID("MainMenuExitButton"))
                    ? (Clay_Color){255, 100, 100, 255}
                    : (Clay_Color){100, 100, 100, 255}
            }) {
                Clay_OnHover(main_menu_hover_handler, (uintptr_t)ui_window);

                CLAY_TEXT(CLAY_STRING("Exit"), CLAY_TEXT_CONFIG({
                    .fontSize = 1 * scale,
                    .textColor = {255, 255, 255, 255},
                    .textAlignment = CLAY_TEXT_ALIGN_CENTER
                }));
            }
        }
    }
    ui_window->array = Clay_EndLayout();
}

static ship_t ui_window_main_menu_ship;

static void ui_window_render_main_menu(ui_window_t* ui_window) {
    window_set_color(ui_window->window, 0, 0, 0, 255);
    window_clear(ui_window->window);

    window_set_color(ui_window->window, 64, 0, 64, 255);

    float scale = 4;
    float cx = ui_window->window->size.x / 2.0f / scale;
    float cy = ui_window->window->size.y / 2.0f / scale;

    float max_r = hypotf(ui_window->window->size.x / scale, ui_window->window->size.y / scale);

    const int lines = 16;

    const float time = SDL_GetTicks() / 1000.0f;
    for (int i = 0; i < lines; i++) {
        // base angle
        float base_angle = (float)i / lines * 2.0f * M_PI;

        // rotate over time
        float angle = base_angle + time * 0.5f;

        // oscillate endpoint length
        float offset = sinf(base_angle * 3 + time * 2.0f) * 40.0f;

        float dx = cosf(angle);
        float dy = sinf(angle);

        float x1 = cx + dx * (max_r + offset);
        float y1 = cy + dy * (max_r + offset);

        window_scale(ui_window->window, scale);
        window_render_line(ui_window->window, cx, cy, x1, y1);
        window_scale(ui_window->window, 1);
    }
    cpu_control(&ui_window->main_menu_bg_ship, ui_window->window->mouse.x, ui_window->window->mouse.y);
    update_ship(&ui_window->main_menu_bg_ship, 1.0f/60.0f, ui_window->window->size);
    window_render_ship_full(ui_window->window, &ui_window->main_menu_bg_ship, &((vector2d){0}));
    //k_font_render_centered(ui_window->window, ui_window->value.bg_ship.name,
    //    ui_window->value.bg_ship.x, ui_window->value.bg_ship.y + ui_window->value.bg_ship.size, 1);

    ui_window_draw(ui_window);
}
