#pragma once

#define CLAY_IMPLEMENTATION
#include "clay.h"

#include "../window.h"
#include "../../font/k_font.h"

typedef struct ui_window_t {
    window_t* window;
    Clay_RenderCommandArray array;
    Clay_Arena arena;
    enum {
        UI_WINDOW_STATE_MAIN_MENU,
        UI_WINDOW_STATE_LOCAL_GAME
    } state;
    ship_t main_menu_bg_ship;
    union {
        struct {
            map_state_h map;
            ship_t ship;
            vector2d offset;
        } local_data;
    } value;
} ui_window_t;

static void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

static Clay_Dimensions clay_measure_text(Clay_StringSlice text, Clay_TextElementConfig* config, void* userData) {
    int w, h;
    k_font_measure(text.chars, text.length, &w, &h);
    return (Clay_Dimensions) {w * config->fontSize, h * config->fontSize};
}

static ui_window_t ui_window_create(window_t* window) {
    ui_window_t ui_window = {.window = window};
    const uint64_t totalMemorySize = Clay_MinMemorySize();
    ui_window.arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
    Clay_Initialize(ui_window.arena,
        (Clay_Dimensions) { window->size.x, window->size.y },
        (Clay_ErrorHandler) { HandleClayErrors }
    );
    ui_window.state = UI_WINDOW_STATE_MAIN_MENU;
    ui_window.main_menu_bg_ship = (ship_t) {
        .state = {
            window->size.x/2, window->size.y/2,
            0, 0,
            0, 0,
            20.0f,
            0, 0
        },
        .input_buffer = {0}
    };
    Clay_SetMeasureTextFunction(clay_measure_text, 0);
    return ui_window;
}

static void ui_window_switch_to_main_menu(ui_window_t* ui_window) {
    ui_window->state = UI_WINDOW_STATE_MAIN_MENU;
}

static void ui_window_switch_to_local_game(ui_window_t* ui_window) {
    ui_window->state = UI_WINDOW_STATE_LOCAL_GAME;
    ui_window->value.local_data.map = (map_state_h){{4800, 4800}};
    ui_window->value.local_data.ship = (ship_t) {
        .state = {
            ui_window->window->size.x/2, ui_window->window->size.y/2,
            0, 0,
            0, 0,
            20.0f,
            0, 0
        },
        .input_buffer = {0}
    };
}

static void ui_window_update(const ui_window_t* ui_window) {
    const window_t* w = ui_window->window;
    const vector2d* m = &w->mouse;
    const vector2d* ws = &w->size;
    Clay_SetLayoutDimensions((Clay_Dimensions) { ws->x, ws->y });
    Clay_SetPointerState((Clay_Vector2){m->x, m->y}, w->mouse_down);
}

static void ui_window_draw_clay_command(const ui_window_t* window, const Clay_RenderCommand* cmd) {
    switch (cmd->commandType) {
        case CLAY_RENDER_COMMAND_TYPE_RECTANGLE: {
            window_set_color(window->window,
                cmd->renderData.rectangle.backgroundColor.r,
                cmd->renderData.rectangle.backgroundColor.g,
                cmd->renderData.rectangle.backgroundColor.b,
                cmd->renderData.rectangle.backgroundColor.a
            );
            window_render_rect(window->window,
                cmd->boundingBox.x, cmd->boundingBox.y,
                cmd->boundingBox.width, cmd->boundingBox.height
            );
            break;
        }
        case CLAY_RENDER_COMMAND_TYPE_TEXT: {
            window_set_color(window->window,
                cmd->renderData.text.textColor.r,
                cmd->renderData.text.textColor.g,
                cmd->renderData.text.textColor.b,
                cmd->renderData.text.textColor.a
            );
            window_set_color(window->window, 255, 255, 255, 255);
            k_font_render(window->window,
                cmd->renderData.text.stringContents.chars,
                cmd->renderData.text.stringContents.length,
                cmd->boundingBox.x, cmd->boundingBox.y,
                cmd->renderData.text.fontSize
            );
            break;
        }
        default:
            break;
    }
}

static void ui_window_draw(const ui_window_t* window) {
    for (size_t i = 0; i < window->array.length; i++) {
        ui_window_draw_clay_command(window, &window->array.internalArray[i]);
    }
}

static Clay_Dimensions clay_measure_render_bounds(const Clay_RenderCommandArray* array) {
    float max_x = 0.0f, max_y = 0.0f;

    for (int32_t i = 0; i < array->length; i++) {
        const Clay_RenderCommand* cmd = &array->internalArray[i];
        max_x = MAX(cmd->boundingBox.x + cmd->boundingBox.width, max_x);
        max_y = MAX(cmd->boundingBox.y + cmd->boundingBox.height, max_y);
    }

    return (Clay_Dimensions){ max_x, max_y };
}


#define CLAY_TRY_MAKE_LAYOUT(render_func, ui_window, max_scale) do {                    \
    for (int scale = (max_scale); scale > 0; scale--) {                                 \
        render_func(ui_window, scale);                                                  \
                                                                                        \
        Clay_Dimensions layout_dim = clay_measure_render_bounds(&((ui_window)->array)); \
        if (layout_dim.width <= ((ui_window)->window->size.x) &&                        \
            layout_dim.height <= ((ui_window)->window->size.y))                         \
            break;                                                                      \
    }                                                                                   \
} while (0)
