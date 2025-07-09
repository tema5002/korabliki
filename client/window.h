#pragma once

#include <SDL3/SDL.h>

#define WIDTH 1920
#define HEIGHT 1000
#define SCALE 1
#define REAL_WIDTH (WIDTH / SCALE)
#define REAL_HEIGHT (HEIGHT / SCALE)

typedef struct window_t {
    SDL_Window* window;
    SDL_Renderer* renderer;
} window_t;

window_t window_create(const char* name, const int width, const int height);
void window_scale(const window_t* window, const float scale);
void window_set_color(const window_t* window, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);

void window_render_line(const window_t* window, const float x1, const float y1, const float x2, const float y2);
void window_render_rect(const window_t* window, const float x, const float y, const float w, const float h);
void window_render_rotated_square(const window_t* window, const float x, const float y, const float size, const float angle_rad);
void window_render_arrow(const window_t* window, const float x, const float y, const float dx, const float dy);
void window_render_arrow_angle(const window_t* window, const float x, const float y, const float angle, const float size);