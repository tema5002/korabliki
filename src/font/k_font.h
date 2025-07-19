#pragma once

#include "../rendering/window.h"
#include "k_font_ascii.h"
#include "k_font_cyrillic.h"

static uint32_t k_utf8_decode(const char* s, size_t* offset) {
    const uint8_t *p = (const uint8_t *) s + *offset;
    uint32_t cp = 0;

    if (p[0] < 0x80) {
        cp = p[0];
        *offset += 1;
    } else if ((p[0] & 0xE0) == 0xC0) {
        cp = ((p[0] & 0x1F) << 6)
             | (p[1] & 0x3F);
        *offset += 2;
    } else if ((p[0] & 0xF0) == 0xE0) {
        cp = ((p[0] & 0x0F) << 12)
             | ((p[1] & 0x3F) << 6)
             | (p[2] & 0x3F);
        *offset += 3;
    } else if ((p[0] & 0xF8) == 0xF0) {
        cp = ((p[0] & 0x07) << 18)
             | ((p[1] & 0x3F) << 12)
             | ((p[2] & 0x3F) << 6)
             | (p[3] & 0x3F);
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

static void k_font_draw(
    const window_t *window,
    const uint8_t *glyph,
    const int width,
    const float x,
    const float y,
    const float scale
) {
    window_set_color(window, 255, 255, 255, 255);
    for (int j = 0; j < K_FONT_HEIGHT; j++) {
        for (int i = 0; i < width; i++) {
            const int bit_index = j * K_FONT_HEIGHT + i;
            const int byte_index = bit_index / 8;
            const int bit_in_byte = 7 - (bit_index % 8);
            const uint8_t mask = 1 << bit_in_byte;

            /*
            const int bit_index  = j * width + i;
            const int byte_index = bit_index >> 3;
            const int bit_mask   = 1 << (7 - (bit_index & 7));*/

            if (glyph[byte_index] & mask) {
                window_render_fill_rect(
                    window,
                    x + i * scale, y + j * scale,
                    scale, scale
                );
            }
        }
    }
}

static void k_font_render(
    const window_t *window,
    const char *text,
    const size_t len,
    const float x,
    const float y,
    const float scale
) {
    window_set_color(window, 255, 255, 255, 255);
    float cur_x = x, cur_y = y;
    size_t i = 0;

    while (i < len) {
        if (text[i] == '\n') {
            cur_y += (K_FONT_HEIGHT + 1) * scale;
            cur_x = x;
            i++;
            continue;
        }

        size_t offset = i;
        uint32_t codepoint = k_utf8_decode(text, &offset);

        if (offset > len) break;

        i = offset;

        const uint8_t* g = k_font_get(codepoint);
        const int width = k_font_get_width(codepoint);
        k_font_draw(window, g, width, cur_x, cur_y, scale);
        cur_x += ((float)width + 1) * scale;
    }
}

static void k_font_render_z(const window_t *window, const char *text, const float x, const float y, const float scale) {
    window_set_color(window, 255, 255, 255, 255);
    float cur_x = x, cur_y = y;
    size_t i = 0;

    while (text[i] != '\0') {
        if (text[i] == '\n') {
            cur_y += (K_FONT_HEIGHT + 1) * scale;
            cur_x = x;
            i++;
            continue;
        }

        uint32_t codepoint = k_utf8_decode(text, &i);

        const uint8_t* g = k_font_get(codepoint);
        const int width = k_font_get_width(codepoint);
        k_font_draw(window, g, width, cur_x, cur_y, scale);
        cur_x += ((float)width + 1) * scale;
    }
}

static void k_font_measure(
        const char* text,
        const size_t len,
        int* width,
        int* height
) {
    int max_line_width = 0;
    int current_line_width = 0;
    int line_count = 1;

    size_t i = 0;
    while (i < len) {
        const char c = text[i];

        if (c == '\n') {
            if (current_line_width > max_line_width)
                max_line_width = current_line_width;
            current_line_width = 0;
            line_count++;
            i++;
            continue;
        }

        size_t offset = i;
        if (offset >= len) break;

        uint32_t codepoint = k_utf8_decode(text, &offset);

        if (offset > len) break;

        i = offset;

        const int char_width = k_font_get_width(codepoint);
        current_line_width += char_width + 1;
    }

    if (current_line_width > max_line_width)
        max_line_width = current_line_width;

    if (width) *width  = max_line_width;
    if (height) *height = line_count * (K_FONT_HEIGHT + 1);
}

static void k_font_measure_z(
        const char* text,
        int* width,
        int* height
) {
    int max_line_width = 0;
    int current_line_width = 0;
    int line_count = 1;
    size_t i = 0;

    while (text[i] != '\0') {
        if (text[i] == '\n') {
            if (current_line_width > max_line_width)
                max_line_width = current_line_width;

            current_line_width = 0;
            line_count++;
            i++;
            continue;
        }

        uint32_t codepoint = k_utf8_decode(text, &i);
        int char_width     = k_font_get_width(codepoint);

        current_line_width += char_width + 1;
    }

    if (current_line_width > max_line_width)
        max_line_width = current_line_width;

    if (width)
        *width = max_line_width;
    if (height)
        *height = line_count * (K_FONT_HEIGHT + 1);
}

static void k_font_render_centered(const window_t* window, const char* text, const float x, const float y, const float scale) {
    int width;
    k_font_measure_z(text, &width, NULL);
    k_font_render_z(window, text, x - width/2 * scale, y, scale);
}
