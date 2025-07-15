#pragma once

#include <SDL3/SDL.h>

typedef struct window_t {
    SDL_Window* window;
    SDL_Renderer* renderer;
} window_t;

static window_t window_create(const char* name, const int width, const int height) {
    window_t window;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init(): %s\n", SDL_GetError());
        exit(0);
    }

    window.window = SDL_CreateWindow(
        name,
        width,
        height,
        SDL_WINDOW_RESIZABLE
    );

    if (!window.window) {
        fprintf(stderr, "SDL_CreateWindow(): %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window.renderer = SDL_CreateRenderer(window.window, NULL);
    if (!window.renderer) {
        fprintf(stderr, "SDL_CreateRenderer(): %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return window;
}

static void window_scale(const window_t* window, const float scale) {
    SDL_SetRenderScale(window->renderer, scale, scale);
}

static void window_set_color(const window_t* window, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
    SDL_SetRenderDrawColor(window->renderer, r, g, b, a);
}

static void window_clear(const window_t* window) {
    SDL_RenderClear(window->renderer);
}

static void window_render_point(const window_t* window, const float x, const float y) {
    SDL_RenderPoint(window->renderer, x, y);
}

static void window_render_line(const window_t* window, const float x1, const float y1, const float x2, const float y2) {
    SDL_RenderLine(window->renderer, x1, y1, x2, y2);
}

static void window_render_rect(const window_t* window, const float x, const float y, const float w, const float h) {
    const SDL_FRect rect = {x, y, w, h};
    SDL_RenderRect(window->renderer, &rect);
}

static void window_render_rotated_square(const window_t* window, const float x, const float y, const float size, const float angle_rad) {
    const float half = size / 2.0f;

    SDL_FPoint points[5];

    const float cos_a = cosf(angle_rad);
    const float sin_a = sinf(angle_rad);

    for (int i = 0; i < 4; i++) {
        const float dx = i == 0 || i == 3 ? -half : half;
        const float dy = i < 2 ? -half : half;

        points[i].x = x + dx * cos_a - dy * sin_a;
        points[i].y = y + dx * sin_a + dy * cos_a;
    }

    points[4] = points[0];

    SDL_RenderLines(window->renderer, points, 5);
}

static void window_render_arrow(const window_t* window, const float x, const float y, const float dx, const float dy) {
    const float end_x = x + dx;
    const float end_y = y + dy;

    window_render_line(window, x, y, end_x, end_y);

    const float len = sqrtf(dx * dx + dy * dy);
    if (len <= 10.0f) return;

    const float ux = dx / len;
    const float uy = dy / len;

    const float perp_x = -uy;
    const float perp_y = ux;

    const float head_length = 10.0f;
    const float wing_size = 5.0f;

    const float back_x = end_x - ux * head_length;
    const float back_y = end_y - uy * head_length;

    const float left_x = back_x + perp_x * wing_size;
    const float left_y = back_y + perp_y * wing_size;

    const float right_x = back_x - perp_x * wing_size;
    const float right_y = back_y - perp_y * wing_size;

    window_render_line(window, end_x, end_y, left_x, left_y);
    window_render_line(window, end_x, end_y, right_x, right_y);
}

static void window_render_arrow_angle(const window_t* window, const float x, const float y, const float angle, const float size) {
    window_render_arrow(window, x, y, cosf(angle) * size, sinf(angle) * size);
}

static void window_render(const window_t* window) {
    SDL_RenderPresent(window->renderer);
}