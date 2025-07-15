#pragma once
#include "client_state.h"
#include "../font/k_font.h"
#include "../make_join_request.h"
#include "../structs.h"
#include "../window.h"
#include "ship_renderer.h"

static int client_setup_socket(const char* ip, client_state_t* state) {
    if (!get_sockaddr_in(ip, &state->server_addr)) {
        fprintf(stderr, "invalid ip\n");
        return 0;
    }
    state->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (state->sock < 0) {
        fprintf(stderr, "socket() failed\n");
        return 0;
    }
    const int result = connect(state->sock, (struct sockaddr*)&state->server_addr, sizeof(state->server_addr));
    if (result < 0) {
        perror("connect()");
        return 0;
    }
    return 1;
}

static void* receive_ships_thread(void* arg) {
    client_state_t* state = arg;
    uint8_t* buffer = malloc(sizeof(ship_t) * state->max_ships_size + 1);
    while (1) {
        const ssize_t len = recv(state->sock, buffer, sizeof(ship_t) * state->max_ships_size + 1, 0);
        if (len < 1) {
            perror("recv()");
            exit(EXIT_FAILURE);
        }
        if (buffer[0] != SERVER_REQUEST_SHIPS) {
            printf("unknown server side error\n");
            exit(EXIT_FAILURE);
        }
        state->ships_size = (len - 1) / sizeof(ship_t);
        memcpy(state->ships, buffer + 1, sizeof(ship_t) * state->ships_size);
    }
    free(buffer);
}

static void korabliki_client(const char* ip, const char* username) {
    client_state_t state;
    if (!client_setup_socket(ip, &state)) {
        exit(EXIT_FAILURE);
    }

    char buffer[sizeof(client_join_request_t) + 1];
    buffer[0] = CLIENT_REQUEST_JOIN;
    client_join_request_t* jrequest = (client_join_request_t*)(buffer + 1);
    make_join_request(username, &state, jrequest);
    ssize_t result = send(state.sock, &buffer, sizeof(buffer), 0);
    if (result == -1) {
        perror("send()");
        exit(EXIT_FAILURE);
    }

    char buffer2[sizeof(server_join_request_t) + 1];
    result = recv(state.sock, buffer2, sizeof(buffer2), 0);
    const server_join_request_t* sjrequest = (server_join_request_t*)(buffer2 + 1);

    if (buffer2[0] == SERVER_REQUEST_SERVER_FULL) {
        printf("Server is full\n");
        exit(EXIT_SUCCESS);
    }
    if (buffer2[0] != SERVER_REQUEST_JOIN) {
        printf("unknown server side error\n");
        exit(EXIT_FAILURE);
    }
    if (result == -1) {
        perror("recv()");
        exit(EXIT_FAILURE);
    }

    state.map = sjrequest->map;
    state.max_ships_size = sjrequest->max_ships_size;
    state.ships_size = 0;
    state.ships = malloc(sizeof(ship_t) * state.max_ships_size);

    char window_title[256];
    snprintf(window_title, sizeof(window_title),
        "korabliki at %s:%d, logged as %s",
        inet_ntoa(state.server_addr.sin_addr),
        ntohs(state.server_addr.sin_port),
        jrequest->name
    );
    const window_t window = window_create("test", state.map.width, state.map.height);

    client_input_request_t input_req = {0};
    client_input_request_t old_input_req = input_req;

    pthread_t tid;
    pthread_create(&tid, NULL, receive_ships_thread, &state);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }
        const bool* keys = SDL_GetKeyboardState(NULL);
        input_req.thrust = 0;
        if (keys[SDL_SCANCODE_W]) {
            input_req.thrust = 1;
        }
        else if (keys[SDL_SCANCODE_S]) {
            input_req.thrust = -1;
        }

        input_req.rotate_left = keys[SDL_SCANCODE_A];
        input_req.rotate_right = keys[SDL_SCANCODE_D];
        input_req.dash = keys[SDL_SCANCODE_SPACE];

        if (keys[SDL_SCANCODE_ESCAPE]) {
            running = 0;
        }

        if (*(int*)&old_input_req != *(int*)&input_req) {
            char buffer3[sizeof(client_input_request_t) + 1];
            buffer3[0] = CLIENT_REQUEST_INPUT;
            memcpy(buffer3 + 1, &input_req, sizeof(client_input_request_t));
            const size_t len = send(state.sock, &buffer3, sizeof(buffer3), 0);

            if (len != sizeof(buffer3)) {
                fprintf(stderr, "failed to send input\n");
                exit(EXIT_FAILURE);
            }
            old_input_req = input_req;
        }

        window_set_color(&window, 0, 0, 0, 255);
        window_clear(&window);

        for (size_t i = 0; i < state.ships_size; i++) {
            window_render_ship_full(&window, &state.ships[i]);
            k_font_render_centered(&window, state.ships[i].name, state.ships[i].x, state.ships[i].y + state.ships[i].size);
        }
        //window_render_ship_base_direction(&window, 30, 30, ships[whi.id].size, ships[whi.id].angle, ships[whi.id].input_buffer.thrust);

        window_render(&window);
        SDL_Delay(1000 / 60);
    }
}
