#include <SDL3/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../client/font.h"

#include "ship.h"
#include "../client/ship_renderer.h"
#include "../client/window.h"

#define SHIPS_SIZE (4 + 1)
ship_t ships[SHIPS_SIZE];

int main(int argc, char *argv[]) {
    window_t window = window_create("korabliki", WIDTH, HEIGHT);
    window_scale(&window, SCALE);

    ships[0].x = REAL_WIDTH/2;
    ships[0].y = REAL_HEIGHT/2;
    ships[0].vx = 0;
    ships[0].vy = 0;
    ships[0].angle = 0;
    ships[0].angular_velocity = 0;
    ships[0].size = 20;
    ships[0].dash_timer = 0.0f;
    ships[0].dash_cooldown = 0.0f;

    for (int i = 1; i < sizeof(ships) / sizeof(ship_t); i++) {
        ships[i].x = rand()%REAL_WIDTH,
        ships[i].y = rand()%REAL_HEIGHT;
        ships[i].vx = rand()%REAL_WIDTH;
        ships[i].vy = rand()%REAL_HEIGHT;
        ships[i].angle = rand() / (float)RAND_MAX * 360;
        ships[i].angular_velocity = 0.0f;
        ships[i].size = 20.0f;
        ships[i].dash_timer = 0.0f;
        ships[i].dash_cooldown = 0.0f;
    }

    int running = 1;
    Uint64 last_time = SDL_GetPerformanceCounter();

    while (running) {
        const Uint64 now = SDL_GetPerformanceCounter();
        const float dt = (now - last_time) / (float)SDL_GetPerformanceFrequency();
        last_time = now;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        const bool *keys = SDL_GetKeyboardState(NULL);
        int thrust = 0;
        if (keys[SDL_SCANCODE_W]) {
            thrust = 1;
        }
        else if (keys[SDL_SCANCODE_S]) {
            thrust = -1;
        }
        const int rotate_left = keys[SDL_SCANCODE_A];
        const int rotate_right = keys[SDL_SCANCODE_D];
        const int dash = keys[SDL_SCANCODE_SPACE];

        if (keys[SDL_SCANCODE_ESCAPE]) {
            running = 0;
        }


        update_ship(&ships[0], thrust, rotate_left, rotate_right, dash, dt);
        window_render_ship_base_direction(&window, 30, 30, ships[0].size, ships[0].angle, thrust);
        window_render_ship_full(&window, &ships[0], thrust);
        /*
        SDL_SetRenderScale(renderer, SCALE*2, SCALE*2);
        render_text_centered(renderer, "you", ships[0].x/2, ships[0].y/2 + 15/2);
        SDL_SetRenderScale(renderer, SCALE, SCALE);*/

        for (int i = 1; i < SHIPS_SIZE; i++) {
            int thrust2; bool rotate_left2; bool rotate_right2;

            /*
            ai_control(
                &ships[i],
                sinf(now/1000000000)*200 + REAL_WIDTH/2, REAL_HEIGHT/2,
                &thrust2, &rotate_left2, &rotate_right2
            );
            */


            ai_control(
                &ships[i],
                ships[0].x, ships[0].y,
                &thrust2, &rotate_left2, &rotate_right2
            );

            float mouse_x, mouse_y;
            const Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
            /*
            ai_control(
                &ships[i],
                mouse_x, mouse_y,
                &thrust2, &rotate_left2, &rotate_right2
            );
            */
            if (buttons & SDL_BUTTON_LMASK) {
                float dx = ships[i].x - mouse_x;
                float dy = ships[i].y - mouse_y;

                const float dist = sqrtf(dx*dx + dy*dy);
                if (dist > 0.001f) {
                    dx /= dist;
                    dy /= dist;
                }

                if (dist < 100.0f) {
                    const float speed = 50.0f;
                    ships[i].vx += dx * speed;
                    ships[i].vy += dy * speed;
                }
            }


            update_ship(&ships[i], thrust2, rotate_left2, rotate_right2, false, dt);

            window_render_ship_base_direction(&window, ships[i].x, ships[i].y, ships[i].size, ships[i].angle, thrust2);
            char text_buf[16];
            snprintf(text_buf, sizeof(text_buf), "ship %i", i);
            render_text_centered(&window, text_buf, ships[i].x, ships[i].y + 15);
        }




        SDL_RenderPresent(window.renderer);
    }
    
    SDL_DestroyRenderer(window.renderer);
    SDL_DestroyWindow(window.window);
    SDL_Quit();
    
    return 0;
}