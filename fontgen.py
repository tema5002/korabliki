import sys
from PIL import Image

if len(sys.argv) != 3:
    print(f"usage: {sys.argv[0]} name glyph_size")
    sys.exit(1)

name = sys.argv[1]
glyph_size = int(sys.argv[2])

img = Image.open(f"assets/font/{name}.png").convert("RGB")
width, height = img.size
cols = width // glyph_size
rows = height // glyph_size
total_glyphs = cols * rows
bits_per_glyph = glyph_size * glyph_size
bytes_per_glyph = bits_per_glyph // 8

glyphs = []
glyph_widths = []
for row in range(rows):
    for col in range(cols):
        bits = []
        max_width = 0
        for y in range(glyph_size):
            for x in range(glyph_size):
                r, g, b = img.getpixel((x + col * glyph_size, y + row * glyph_size))
                if r == g == b == 0xFF:
                    max_width = max(max_width, x + 1);
                bits.append(r == g == b == 0xFF)

        packed = []
        for i in range(0, len(bits), 8):
            byte = 0
            for j in range(8):
                if i + j < len(bits):
                    byte |= bits[i + j] << (7 - j)
            packed.append(byte)
        glyphs.append(packed)
        glyph_widths.append(max_width)

if name == "k_font_ascii":
    glyph_widths[ord(' ')] = 3

with open(f"src/font/{name}.h", "w") as f:
    f.write("#pragma once\n#include <stdint.h>\n\n")
    f.write(f"#ifndef K_FONT_HEIGHT\n#define K_FONT_HEIGHT {glyph_size}\n#endif\n")
    f.write(f"static uint8_t {name}[{total_glyphs}][{bytes_per_glyph}]=")
    first = True

    f.write("{")
    for g in glyphs:
        if first: first = False
        else: f.write(",")
        line = "{" + ",".join(map(str, g)) + "}"
        f.write(line)
    f.write("};\n")
    f.write(f"static const int {name}_width[{total_glyphs}]=")
    f.write("{")
    f.write(",".join(map(str, glyph_widths)))
    f.write("};\n")

