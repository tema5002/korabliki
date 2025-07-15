#pragma once

#include "../window.h"
#include "k_font_ascii.h"
#include "k_font_cyrillic.h"

static uint32_t k_utf8_decode(const char *s, size_t *offset) {
    const uint8_t *p = (const uint8_t*)s + *offset;
    uint32_t cp = 0;

    if (p[0] < 0x80) {
        cp = p[0];
        *offset += 1;
    } else if ((p[0] & 0xE0) == 0xC0) {
        cp = ((p[0] & 0x1F) << 6) | (p[1] & 0x3F);
        *offset += 2;
    } else if ((p[0] & 0xF0) == 0xE0) {
        cp = ((p[0] & 0x0F) << 12) | ((p[1] & 0x3F) << 6) | (p[2] & 0x3F);
        *offset += 3;
    } else if ((p[0] & 0xF8) == 0xF0) {
        cp = ((p[0] & 0x07) << 18) | ((p[1] & 0x3F) << 12) |
             ((p[2] & 0x3F) << 6)  | (p[3] & 0x3F);
        *offset += 4;
    } else {
        cp = 0xFFFD;
        *offset += 1;
    }

    return cp;
}


static uint8_t* k_font_get(const int idx) {
    if (0 <= idx && idx <= 0x7f)
        return k_font_ascii[idx];
    if (0x400 <= idx && idx <= 0x4ff)
        return k_font_cyrillic[idx - 0x400];
    return k_font_ascii['\0'];
}

static int k_font_get_width(const int idx) {
    if (0 <= idx && idx <= 0x7f)
        return k_font_ascii_width[idx];
    if (0x400 <= idx && idx <= 0x4ff)
        return k_font_cyrillic_width[idx - 0x400];
    return k_font_ascii_width['\0'];
}

static void k_font_draw(const window_t* window, const uint8_t* g, const int width, const float x, const float y) {
    for (int j = 0; j < K_FONT_HEIGHT; j++) {
        for (int i = 0; i < width; i++) {
            int bit_index = j * K_FONT_HEIGHT + i;
            int byte_index = bit_index / 8;
            int bit_in_byte = 7 - (bit_index % 8);

            if ((g[byte_index] >> bit_in_byte) & 1) {
                window_render_point(window, x + (float)i, y + (float)j);
            }
        }
    }
}

static void k_font_render(const window_t* window, const char* text, const float x, const float y) {
    window_set_color(window, 255, 255, 255, 255);
    float cur_x = x, cur_y = y;
    size_t i = 0;

    while (text[i] != '\0') {
        if (text[i] == '\n') {
            cur_y += K_FONT_HEIGHT + 1;
            cur_x = x;
            i++;
            continue;
        }

        uint32_t codepoint = k_utf8_decode(text, &i);

        const uint8_t* g = k_font_get(codepoint);
        const int width = k_font_get_width(codepoint);
        k_font_draw(window, g, width, cur_x, cur_y);
        cur_x += (float)width + 1;
    }
}

static int k_font_width(const char* text) {
    int max_x = 0;
    int x = 0;
    size_t i = 0;
    while (text[i] != '\0') {
        if (text[i] == '\n') {
            max_x = MAX(max_x, x);
            x = 0;
            i++;
            continue;
        }

        uint32_t codepoint = k_utf8_decode(text, &i);

        const int width = k_font_get_width(codepoint);
        x += width + 1;
    }
    max_x = MAX(max_x, x);
    return max_x;
}

static void k_font_render_centered(const window_t* window, const char* text, const float x, const float y) {
    const int width = k_font_width(text);
    k_font_render(window, text, x - width/2, y);
}
