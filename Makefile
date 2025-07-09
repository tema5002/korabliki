CC = clang
CFLAGS = -Wall -Wextra -O3 -std=c99 -D_XOPEN_SOURCE=500 -Wunused-function
LDFLAGS = -O3 -lSDL3 -lm

CLIENT_SRC = client
CLIENT_SRCS = $(shell find $(CLIENT_SRC) -type f -name '*.c')
CLIENT_OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(CLIENT_SRCS))

SERVER_SRC = server
SERVER_SRCS = $(shell find $(SERVER_SRC) -type f -name '*.c')
SERVER_OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SERVER_SRCS))

SHARED_SRC = shared
SHARED_SRCS = $(shell find $(SHARED_SRC) -type f -name '*.c')
SHARED_OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SHARED_SRCS))

CLIENT_TARGET = korabliki
SERVER_TARGET = korabliki_server

OBJ_DIR = obj

all: $(CLIENT_TARGET) $(SERVER_TARGET)

$(CLIENT_TARGET): $(CLIENT_OBJS) $(SHARED_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(SERVER_TARGET): $(SERVER_OBJS) $(SHARED_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/client/%.o: $(CLIENT_SRC)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/server/%.o: $(SERVER_SRC)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/shared/%.o: $(SHARED_SRC)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(CLIENT_TARGET) $(SERVER_TARGET)

.PHONY: all clean
