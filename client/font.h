#pragma once

#include "window.h"

#define GLYPH_HEIGHT 10
#define LETTER_SPACING 1

typedef struct {
    char ch;
    const char *pattern[GLYPH_HEIGHT];
    int width;
} font_glyph;

extern const font_glyph glyphs[];
extern const int num_glyphs;

const font_glyph* find_glyph(const char c);
void draw_glyph(const window_t* window, const font_glyph* g, const float x, const float y);
void render_text(const window_t* window, const char* text, const float x, const float y);
void render_text_centered(const window_t* window, const char* text, const float x, const float y);
void measure_text(const char* text, int* width, int* height);
