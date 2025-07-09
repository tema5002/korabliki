#include "font.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

const font_glyph glyphs[] = {
    {
        ' ', {
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   "
        },
        3
    },
    {
        '!', {
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "  ",
            "XX",
            "  ",
            "  "
        },
        2
    },
    {
        '"', {
            "XX XX",
            "XX XX",
            "X  X ",
            "     ",
            "     ",
            "     ",
            "     ",
            "     ",
            "     ",
            "     "
        },
        5
    },
    {
        '#', {
            "       ",
            " XX XX ",
            "XXXXXXX",
            " XX XX ",
            " XX XX ",
            "XXXXXXX",
            " XX XX ",
            "       ",
            "       ",
            "       "
        },
        7
    },
    {
        '$', {
            "   XX  ",
            " XXXXXX",
            "XX     ",
            " XXXXX ",
            "     XX",
            "     XX",
            "XXXXXX ",
            "  XX   ",
            "       ",
            "       "
        },
        7
    },
    {
        '%', {
            "XX    X",
            "XX   XX",
            "    XX ",
            "   XX  ",
            "  XX   ",
            " XX    ",
            "XX   XX",
            "X    XX",
            "       ",
            "       "
        },
        7
    },
    {
        '&', {
            "  XXX  ",
            " XX XX ",
            " XX XX ",
            "  XXX  ",
            " XXX XX",
            "XX XXX ",
            "XX  XX ",
            " XXX XX",
            "       ",
            "       "
        },
        7
    },
    {
        '\'', {
            " XX",
            " XX",
            "XX ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   "
        },
        3
    },
    {
        '(', {
            "  XX",
            " XX ",
            "XX  ",
            "XX  ",
            "XX  ",
            "XX  ",
            " XX ",
            "  XX",
            "    ",
            "    "
        },
        4
    },
    {
        ')', {
            "XX  ",
            " XX ",
            "  XX",
            "  XX",
            "  XX",
            "  XX",
            " XX ",
            "XX  ",
            "    ",
            "    "
        },
        4
    },
    {
        '*', {
            "      ",
            "      ",
            " X  X ",
            "  XX  ",
            "XXXXXX",
            "  XX  ",
            " X  X ",
            "      ",
            "      ",
            "      "
        },
        6
    },
    {
        '+', {
            "      ",
            "      ",
            "  XX  ",
            "  XX  ",
            "XXXXXX",
            "  XX  ",
            "  XX  ",
            "      ",
            "      ",
            "      "
        },
        6
    },
    {
        ',', {
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            " XX",
            " XX",
            "XX ",
            "   "
        },
        3
    },
    {
        '-', {
            "      ",
            "      ",
            "      ",
            "      ",
            "XXXXXX",
            "      ",
            "      ",
            "      ",
            "      ",
            "      "
        },
        6
    },
    {
        '.', {
            "  ",
            "  ",
            "  ",
            "  ",
            "  ",
            "  ",
            "XX",
            "XX",
            "  ",
            "  "
        },
        2
    },
    {
        '/', {
            "      X",
            "     XX",
            "    XX ",
            "   XX  ",
            "  XX   ",
            " XX    ",
            "XX     ",
            "X      ",
            "       ",
            "       "
        },
        7
    },
    {
        ':', {
            "  ",
            "  ",
            "XX",
            "XX",
            "  ",
            "XX",
            "XX",
            "  ",
            "  ",
            "  "
        },
        2
    },
    {
        '<', {
            "     ",
            "   XX",
            "  XX ",
            " XX  ",
            "XX   ",
            " XX  ",
            "  XX ",
            "   XX",
            "     ",
            "     "
        },
        5
    },
    {
        '=', {
            "     ",
            "     ",
            "     ",
            "XXXXX",
            "     ",
            "XXXXX",
            "     ",
            "     ",
            "     ",
            "     "
        },
        5
    },
    {
        '>', {
            "     ",
            "XX   ",
            " XX  ",
            "  XX ",
            "   XX",
            "  XX ",
            " XX  ",
            "XX   ",
            "     ",
            "     "
        },
        5
    },
    {
        '?', {
            " XXXXX ",
            "XX   XX",
            "     XX",
            "    XX ",
            "   XX  ",
            "  XX   ",
            "       ",
            "  XX   ",
            "       ",
            "       "
        },
        7
    },
    {
        '@', {
            " XXXXX ",
            "X     X",
            "X  XX X",
            "X X   X",
            "X X   X",
            "X  XX X",
            "X     X",
            " XXXXX ",
            "       ",
            "       "
        },
        7
    },
    {
        'A', {
            "   X   ",
            "  XXX  ",
            " XX XX ",
            "XX   XX",
            "XXXXXXX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "       ",
            "       "
        },
        7
    },
    {
        'B', {
            "XXXXX  ",
            "XX  XX ",
            "XX  XX ",
            "XXXXXXX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XXXXXX ",
            "       ",
            "       "
        },
        7
    },
    {
        'C', {
            " XXXXX ",
            "XX   XX",
            "XX     ",
            "XX     ",
            "XX     ",
            "XX     ",
            "XX   XX",
            " XXXXX ",
            "       ",
            "       "
        },
        7
    },
    {
        'D', {
            "XXXX   ",
            "XX XX  ",
            "XX  XX ",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XXXXXX ",
            "       ",
            "       "
        },
        7
    },
    {
        'E', {
            "XXXXXXX",
            "XX     ",
            "XX     ",
            "XXXXX  ",
            "XX     ",
            "XX     ",
            "XX     ",
            "XXXXXXX",
            "       ",
            "       "
        },
        7
    },
    {
        'F', {
            "XXXXXXX",
            "XX     ",
            "XX     ",
            "XXXXX  ",
            "XX     ",
            "XX     ",
            "XX     ",
            "XX     ",
            "       ",
            "       "
        },
        7
    },
    {
        'F', {
            " XXXXX ",
            "XX   XX",
            "XX     ",
            "XX XXXX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            " XXXXX ",
            "       ",
            "       "
        },
        7
    },
    {
        'H', {
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XXXXXXX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "       ",
            "       "
        },
        7
    },
    {
        'I', {
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "  ",
            "  "
        },
        2
    },
    {
        'J', {
            "     XX",
            "     XX",
            "     XX",
            "     XX",
            "     XX",
            "     XX",
            "XX   XX",
            " xxxxx ",
            "       ",
            "       "
        },
        7
    },
    {
        'K', {
            "XX   XX",
            "XX  XX ",
            "XX XX  ",
            "XXXX   ",
            "XX XX  ",
            "XX  XX ",
            "XX   XX",
            "XX   XX",
            "       ",
            "       "
        },
        7
    },
    {
        'L', {
            "XX     ",
            "XX     ",
            "XX     ",
            "XX     ",
            "XX     ",
            "XX     ",
            "XX     ",
            "XXXXXXX",
            "       ",
            "       "
        },
        7
    },
    {
        'M', {
            "XX    XX",
            "XXX  XXX",
            "XXXXXXXX",
            "XX XX XX",
            "XX    XX",
            "XX    XX",
            "XX    XX",
            "XX    XX",
            "        ",
            "        "
        },
        8
    },
    {
        'N', {
            "XX    XX",
            "XXX   XX",
            "XXXX  XX",
            "XX XX XX",
            "XX  XXXX",
            "XX   XXX",
            "XX    XX",
            "XX    XX",
            "        ",
            "        "
        },
        8
    },
    {
        'O', {
            " XXXXXX ",
            "XX    XX",
            "XX    XX",
            "XX    XX",
            "XX    XX",
            "XX    XX",
            "XX    XX",
            " XXXXXX ",
            "        ",
            "        "
        },
        8
    },
    {
        'P', {
            "XXXXXX ",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XXXXXX ",
            "XX     ",
            "XX     ",
            "XX     ",
            "       ",
            "       "
        },
        7
    },
    {
        'Q', {
            " XXXXX ",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XX     ",
            " XXXXXX",
            "       ",
            "       "
        },
        7
    },
    {
        'R', {
            "XXXXXX ",
            "XX   XX",
            "XX   XX",
            "XXXXXX ",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "       ",
            "       "
        },
        7
    },
    {
        'S', {
            " XXXXX ",
            "XX   XX",
            "XX     ",
            " XXXXX ",
            "     XX",
            "     XX",
            "XX   XX",
            " XXXXX ",
            "       ",
            "       "
        },
        7
    },
    {
        'T', {
            "XXXXXXXX",
            "   XX   ",
            "   XX   ",
            "   XX   ",
            "   XX   ",
            "   XX   ",
            "   XX   ",
            "   XX   ",
            "        ",
            "        "
        },
        8
    },
    {
        'U', {
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            " XXXXX ",
            "       ",
            "       "
        },
        7
    },
    {
        'V', {
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            "XX   XX",
            " XX XX ",
            "  XXX  ",
            "   X   ",
            "       ",
            "       "
        },
        7
    },
    {
        'W', {
            "XX    XX",
            "XX    XX",
            "XX    XX",
            "XX XX XX",
            "XX XX XX",
            "XXXXXXXX",
            "XXX  XXX",
            "XX    XX",
            "        ",
            "        "
        },
        8
    },
    {
        'X', {
            "XX    XX",
            "XX    XX",
            " XX  XX ",
            "  XXXX  ",
            " XX  XX ",
            "XX    XX",
            "XX    XX",
            "XX    XX",
            "        ",
            "        "
        },
        8
    },
    {
        'Y', {
            "XX    XX",
            "XX    XX",
            " XX  XX ",
            "  XXXX  ",
            "   XX   ",
            "   XX   ",
            "   XX   ",
            "   XX   ",
            "        ",
            "        "
        },
        8
    },
    {
        'Z', {
            "XXXXXXXX",
            "      XX",
            "     XX ",
            "   XX   ",
            "  XX    ",
            " XX     ",
            "XX      ",
            "XXXXXXXX",
            "        ",
            "        "
        },
        8
    },
    {
        '[', {
            "XXXX",
            "XX  ",
            "XX  ",
            "XX  ",
            "XX  ",
            "XX  ",
            "XX  ",
            "XXXX",
            "    ",
            "    "
        },
        4
    },
    {
        '\\', {
            "X      ",
            "XX     ",
            " XX    ",
            "  XX   ",
            "   XX  ",
            "    XX ",
            "     XX",
            "      X",
            "       ",
            "       "
        },
        7
    },
    {
        ']', {
            "XXXX",
            "  XX",
            "  XX",
            "  XX",
            "  XX",
            "  XX",
            "  XX",
            "XXXX",
            "    ",
            "    "
        },
        4
    },
    {
        '^', {
            // triton productions what the hell is this bruh
            "XXXX",
            "XXXX",
            "XXXX",
            "XXXX",
            "XXXX",
            "XXXX",
            "XXXX",
            "XXXX",
            "XXXX",
            "XXXX"
        },
        4
    },
    {
        '_', {
            "     ",
            "     ",
            "     ",
            "     ",
            "     ",
            "     ",
            "     ",
            "XXXXX",
            "     ",
            "     "
        },
        5
    },
    {
        '`', {
            "XX ",
            "XX ",
            " XX",
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   "
        },
        3
    },
    {
        'a', {
            "      ",
            "      ",
            "      ",
            " XXXX ",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            " XXXXX",
            "      ",
            "      "
        },
        6
    },
    {
        'b', {
            "XX    ",
            "XX    ",
            "XX    ",
            "XXXXX ",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            "XXXXX ",
            "      ",
            "      "
        },
        6
    },
    {
        'c', {
            "      ",
            "      ",
            "      ",
            " XXXX ",
            "XX  XX",
            "XX    ",
            "XX  XX",
            " XXXX ",
            "      ",
            "      "
        },
        6
    },
    {
        'd', {
            "    XX",
            "    XX",
            "    XX",
            " XXXXX",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            " XXXXX",
            "      ",
            "      "
        },
        6
    },
    {
        'e', {
            "      ",
            "      ",
            "      ",
            " XXXX ",
            "XX  XX",
            "XXXXXX",
            "XX    ",
            " XXXXX",
            "      ",
            "      "
        },
        6
    },
    {
        'f', {
            " XXX",
            "XX  ",
            "XXXX",
            "XX  ",
            "XX  ",
            "XX  ",
            "XX  ",
            "XX  ",
            "XX  ",
            "XX  "
        },
        4
    },
    {
        'g', {
            "      ",
            "      ",
            "      ",
            " XXXXX",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            " XXXXX",
            "    XX",
            "XXXXX "
        },
        6
    },
    {
        'h', {
            "XX    ",
            "XX    ",
            "XX    ",
            "XXXXX ",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            "      ",
            "      "
        },
        6
    },
    {
        'i', {
            "  ",
            "XX",
            "  ",
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "  ",
            "  "
        },
        2
    },
    {
        'j', {
            "    ",
            "  XX",
            "    ",
            "  XX",
            "  XX",
            "  XX",
            "  XX",
            "  XX",
            "  XX",
            "XXX "
        },
        4
    },
    {
        'k', {
            "XX    ",
            "XX    ",
            "XX    ",
            "XX  XX",
            "XX XX ",
            "XXXX  ",
            "XX XX ",
            "XX  XX",
            "      ",
            "      "
        },
        6
    },
    {
        'l', {
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "  ",
            "  "
        },
        2
    },
    {
        'm', {
            "        ",
            "        ",
            "        ",
            "XXXXXXX ",
            "XX XX XX",
            "XX XX XX",
            "XX XX XX",
            "XX    XX",
            "        ",
            "        "
        },
        8
    },
    {
        'n', {
            "      ",
            "      ",
            "      ",
            "XXXXX ",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            "      ",
            "      "
        },
        6
    },
    {
        'o', {
            "      ",
            "      ",
            "      ",
            " XXXX ",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            " XXXX ",
            "      ",
            "      "
        },
        6
    },
    {
        'p', {
            "      ",
            "      ",
            "      ",
            "XXXXX ",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            "XXXXX ",
            "XX    ",
            "XX    "
        },
        6
    },
    {
        'q', {
            "      ",
            "      ",
            "      ",
            " XXXXX",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            " XXXXX",
            "    XX",
            "    XX"
        },
        6
    },
    {
        'r', {
            "    ",
            "    ",
            "    ",
            " XXX",
            "XX  ",
            "XX  ",
            "XX  ",
            "XX  ",
            "    ",
            "    "
        },
        4
    },
    {
        's', {
            "      ",
            "      ",
            "      ",
            " XXXXX",
            "XX    ",
            " XXXX ",
            "    XX",
            "XXXXX ",
            "      ",
            "      "
        },
        6
    },
    {
        't', {
            "    ",
            "XX  ",
            "XX  ",
            "XXXX",
            "XX  ",
            "XX  ",
            "XX  ",
            " XXX",
            "    ",
            "    "
        },
        4
    },
    {
        'u', {
            "      ",
            "      ",
            "      ",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            " XXXXX",
            "      ",
            "      "
        },
        6
    },
    {
        'v', {
            "       ",
            "       ",
            "       ",
            "XX   XX",
            "XX   XX",
            " XX XX ",
            "  XXX  ",
            "   X   ",
            "       ",
            "       "
        },
        7
    },
    {
        'w', {
            "        ",
            "        ",
            "        ",
            "XX XX XX",
            "XX XX XX",
            "XX XX XX",
            "XX XX XX",
            " XXXXXXX",
            "        ",
            "        "
        },
        8
    },
    {
        'x', {
            "        ",
            "        ",
            "        ",
            "XX   XX",
            " XX XX ",
            "  XXX  ",
            " XX XX ",
            "XX   XX",
            "        ",
            "        "
        },
        7
    },
    {
        'y', {
            "      ",
            "      ",
            "      ",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            " XXXXX",
            "    XX",
            "XXXXX "
        },
        6
    },
    {
        'z', {
            "       ",
            "       ",
            "       ",
            "XXXXXX",
            "   XX ",
            "  XX  ",
            " XX   ",
            "XXXXXX",
            "       ",
            "       "
        },
        6
    },
    {
        '{', {
            "  XX",
            " XX ",
            " XX ",
            " XX ",
            "XX  ",
            " XX ",
            " XX ",
            " XX ",
            "  XX",
            "    "
        },
        4
    },
    {
        '|', {
            "  ",
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "XX",
            "  ",
            "  "
        },
        2
    },
    {
        '}', {
            "XX  ",
            " XX ",
            " XX ",
            " XX ",
            "  XX",
            " XX ",
            " XX ",
            " XX ",
            "XX  ",
            "    "
        },
        4
    },
    {
        '0', {
            " XXXX ",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            " XXXX ",
            "      ",
            "      "
        },
        6
    },

    {
        '1', {
            "  XX  ",
            " XXX  ",
            "  XX  ",
            "  XX  ",
            "  XX  ",
            "  XX  ",
            "  XX  ",
            "XXXXXX",
            "      ",
            "      "
        },
        6
    },
    {
        '2', {
            " XXXX ",
            "XX  XX",
            "    XX",
            "   XX ",
            "  XX  ",
            " XX   ",
            "XX    ",
            "xXXXXx",
            "      ",
            "      "
        },
        6
    },
    {
        '3', {
            " XXXX ",
            "XX  XX",
            "    XX",
            "  XXX ",
            "    XX",
            "    XX",
            "XX  XX",
            " XXXX ",
            "      ",
            "      "
        },
        6
    },
    {
        '4', {
            "XX  XX",
            "XX  XX",
            "XX  XX",
            "XXXXXX",
            "    XX",
            "    XX",
            "    XX",
            "    XX",
            "      ",
            "      "
        },
        6
    },
    {
        '5', {
            "XXXXXX",
            "XX    ",
            "XX    ",
            "XXXXX ",
            "    XX",
            "    XX",
            "XX  XX",
            " XXXX ",
            "      ",
            "      "
        },
        6
    },
    {
        '6', {
            " XXXX ",
            "XX  XX",
            "XX    ",
            "XXXXX ",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            " XXXX ",
            "      ",
            "      "
        },
        6
    },
    {
        '7', {
            "XXXXXX",
            "    XX",
            "    XX",
            "   XX ",
            "  XX  ",
            "  XX  ",
            "  XX  ",
            "  XX  ",
            "      ",
            "      "
        },
        6
    },
    {
        '8', {
            " XXXX ",
            "XX  XX",
            "XX  XX",
            " XXXX ",
            "XX  XX",
            "XX  XX",
            "XX  XX",
            " XXXX ",
            "      ",
            "      "
        },
        6
    },
    {
        '9', {
            " XXXX ",
            "XX  XX",
            "XX  XX",
            " XXXXX",
            "    XX",
            "    XX",
            "XX  XX",
            " XXXX ",
            "      ",
            "      "
        },
        6
    }
};

const int num_glyphs = sizeof(glyphs) / sizeof(glyphs[0]);

const font_glyph* find_glyph(const char c) {
    for (int i = 0; i < num_glyphs; i++) {
        if (glyphs[i].ch == c)
            return &glyphs[i];
    }
    return NULL;
}

void draw_glyph(const window_t* window, const font_glyph* g, const float x, const float y) {
    for (int j = 0; j < GLYPH_HEIGHT; j++) {
        for (int i = 0; i < g->width; i++) {
            if (g->pattern[j][i] != ' ') {
                SDL_RenderPoint(window->renderer, x + (float)i, y + (float)j);
            }
        }
    }
}

void render_text(const window_t* window, const char* text, const float x, const float y) {
    float cur_x = x, cur_y = y;
    for (size_t i = 0; text[i] != '\0'; i++) {
        const char c = text[i];
        if (c == '\n') {
            cur_y += GLYPH_HEIGHT + 1;
            cur_x = x;
        }
        else {
            const font_glyph* g = find_glyph(c);
            if (!g) continue;
            SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
            draw_glyph(window, g, cur_x, cur_y);
            cur_x += (float)g->width + LETTER_SPACING;
        }
    }
}

void measure_text(const char* text, int* width, int* height) {
    *width = 0;
    *height = GLYPH_HEIGHT;
    int cur_x = 0;
    for (size_t i = 0;; i++) {
        const char c = text[i];
        if (c == '\n') {
            *width = MAX(*width, cur_x);
            cur_x = 0;
            *height += GLYPH_HEIGHT + 1;
        }
        else if (c == '\0') {
            *width = MAX(*width, cur_x);
            return;
        }
        else {
            const font_glyph* g = find_glyph(c);
            if (!g) continue;
            if (cur_x != 0)
                cur_x += LETTER_SPACING;
            cur_x += g->width;
        }
    }
}

void render_text_centered(const window_t* window, const char* text, const float x, const float y) {
    int width, _;
    measure_text(text, &width, &_);
    render_text(window, text, x - (float)width / 2.0f, y);
}
