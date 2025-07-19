CC = clang
CFLAGS = -Wall -std=c99 -D_XOPEN_SOURCE=500
LDFLAGS = -lSDL3 -lopenmpt -lm

CLIENT = korabliki

FONT_PNGS = $(wildcard assets/font/*.png)
FONT_HEADERS = $(FONT_PNGS:assets/font/%.png=src/font/%.h)

all: $(CLIENT)

src/font/%.h: fontgen.py assets/font/%.png
	mkdir -p src/font
	python3 fontgen.py $* 12

$(CLIENT): $(FONT_HEADERS) src/main.c $(wildcard src/*.h src/server/*.h src/client/*.h)
	$(CC) src/client.c -o $(CLIENT) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(FONT_HEADERS)

.PHONY: all clean
