#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <pwd.h>
#include <stdlib.h>

#include "ship_renderer.h"
#include "window.h"
#include "font.h"
#include "../shared/get_sockaddr_in.h"
#include "../shared/ship_net.h"

int sock;
struct sockaddr_in server_addr;

ship_t ships[MAX_PLAYERS];

void* receive_thread(void* unused) {
    (void)unused;
    while (1) {
        const size_t len = recv(sock, ships, sizeof(ships), 0);
        if (len != sizeof(ships)) {
            fprintf(stderr, "failed to receive ships\n");
            exit(EXIT_FAILURE);
        }
    }
}

register_packet_t get_register_packet(const char* name) {
    register_packet_t packet;
    packet.color_r = 255; packet.color_g = 255; packet.color_b = 0;
    if (name) {
        strncpy(packet.name, name, sizeof(packet.name));
        return packet;
    }

    const struct passwd* pw = getpwuid(getuid());
    if (pw) {
        strncpy(packet.name, pw->pw_name, sizeof(packet.name) - 1);
        packet.name[sizeof(packet.name) - 1] = '\0';
    }
    else {
        struct sockaddr_in self_addr;
        socklen_t len = sizeof(self_addr);
        getsockname(sock, (struct sockaddr*)&self_addr, &len);
        snprintf(packet.name, sizeof(packet.name), "%s:%d", inet_ntoa(self_addr.sin_addr), ntohs(self_addr.sin_port));
    }
    return packet;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s [ip]:[port] [username]\n", argv[0]);
        return 1;
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_addr = get_sockaddr_in(argv[1]);
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "failed to connect\n");
        return 1;
    }
    register_packet_t packet = get_register_packet(argc < 3 ? NULL : argv[2]);
    send(sock, &packet, sizeof(packet), 0);
    registered_packet_t whi;
    size_t len = recv(sock, &whi, sizeof(whi), 0);

    if (len != sizeof(registered_packet_t)) {
        fprintf(stderr, "failed to receive register reply packet\n");
        return 1;
    }

    if (whi.id == -1) {
        fprintf(stderr, "server is full\n");
        return 1;
    }

    char window_title[256];
    snprintf(window_title, sizeof(window_title),
        "korabliki at %s:%d, logged as %s", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port), packet.name);
    const window_t window = window_create(window_title, whi.width, whi.height);

    pthread_t tid;
    pthread_create(&tid, NULL, receive_thread, NULL);

    ship_input_packet_t input_packet = {0};
    ship_input_packet_t old_input_packet = input_packet;

    bool running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        const bool *keys = SDL_GetKeyboardState(NULL);
        input_packet.thrust = 0;
        if (keys[SDL_SCANCODE_W]) {
            input_packet.thrust = 1;
        }
        else if (keys[SDL_SCANCODE_S]) {
            input_packet.thrust = -1;
        }
        input_packet.rotate_left = keys[SDL_SCANCODE_A];
        input_packet.rotate_right = keys[SDL_SCANCODE_D];
        input_packet.dash = keys[SDL_SCANCODE_SPACE];

        if (keys[SDL_SCANCODE_ESCAPE]) {
            running = 0;
        }

        if (*(int*)&input_packet != *(int*)&old_input_packet) {
            len = send(sock, &input_packet, sizeof(input_packet), 0);
            if (len != sizeof(input_packet)) {
                fprintf(stderr, "failed to send input\n");
                return 1;
            }
            old_input_packet = input_packet;
        }

        window_set_color(&window, 0, 0, 0, 255);
        SDL_RenderClear(window.renderer);

        window_set_color(&window, 255, 255, 255, 255);

        for (int i = 0; i < MAX_PLAYERS; i++) {
            if (ships[i].connected) {
                window_render_ship_full(&window, &ships[i]);
                render_text_centered(&window, ships[i].name, ships[i].x, ships[i].y + ships[i].size);
            }
        }

        window_render_ship_base_direction(&window, 30, 30, ships[whi.id].size, ships[whi.id].angle, ships[whi.id].input_buffer.thrust);

        SDL_RenderPresent(window.renderer);
        SDL_Delay(1000 / 60);
    }
    return 0;
}
