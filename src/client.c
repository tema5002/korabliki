#include "includes.h"
#include "ship_logic.h"
#include "structs.h"
#include "rendering/window.h"
#include "rendering/ui/ui_window.h"
#include "rendering/ui/main_menu.h"
#include "rendering/ui/local_game.h"

#include "music/jukebox.h"

int main() {
    window_t window = window_create("korabliki", 800, 600);
    ui_window_t ui_window = ui_window_create(&window);

    if (!mod_init()) {
        return 1;
    }

    if (!mod_load_from_file("assets/music/very cool file name.xm")) {
        return 1;
    }

    bool running = true;
    while (running) {
        uint32_t start = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            else if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                running = false;
            }
            else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                window.size.x = event.window.data1;
                window.size.y = event.window.data2;
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                window.mouse_down = true;
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                window.mouse_down = false;
            }
            else if (event.type == SDL_EVENT_MOUSE_MOTION) {
                window.mouse.x = event.motion.x;
                window.mouse.y = event.motion.y;
            }
        }
        ui_window_update(&ui_window);

        switch (ui_window.state) {
            case UI_WINDOW_STATE_MAIN_MENU:
                CLAY_TRY_MAKE_LAYOUT(ui_window_make_main_menu, &ui_window, 3);
                ui_window_render_main_menu(&ui_window);
                break;
            case UI_WINDOW_STATE_LOCAL_GAME:
                CLAY_TRY_MAKE_LAYOUT(ui_window_make_local_game, &ui_window, 3);
                ui_window_render_local_game(&ui_window);
                break;
        }

        window_render(&window);

        const uint32_t end = SDL_GetTicks();
        const int frame_time = end - start;
        SDL_Delay(fmax(0, 16 - frame_time));
    }
}
