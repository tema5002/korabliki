#pragma once
#include "../get_sockaddr_in.h"
#include "server_state.h"
#include "../structs.h"
#include "ship_logic.h"

static int server_setup_socket(const char* ip, server_state_t* state) {
    if (!get_sockaddr_in(ip, &state->server_addr)) {
        fprintf(stderr, "invalid ip\n");
        exit(EXIT_FAILURE);
    }
    state->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (state->sock < 0) {
        fprintf(stderr, "socket() failed\n");
        return 0;
    }
    const int result = bind(state->sock, (struct sockaddr*)&state->server_addr, sizeof(state->server_addr));
    if (result < 0) {
        perror("bind()");
        return 0;
    }
    return 1;
}

static void* accept_packets_thread(void* arg) {
    server_state_t* state = arg;
    while (1) {
        char buffer[CLIENT_REQUEST_MAX_SIZE];

        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);

        const ssize_t len = recvfrom(state->sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &addr_len);
        if (len < 1) {
            perror("recvfrom(state->sock, &request_type, sizeof(request_type), 0, (struct sockaddr*)&client_addr, &addr_len)");
            continue;
        }

        switch (buffer[0]) {
            case CLIENT_REQUEST_JOIN: {
                const client_join_request_t* req = (client_join_request_t*)(buffer + 1);
                if (!register_new_client(state, req, &client_addr)) {
                    const uint8_t c = SERVER_REQUEST_SERVER_FULL;
                    sendto(state->sock, &c, sizeof(c), 0,
                        (struct sockaddr*)&client_addr, sizeof(client_addr)
                    );
                }
                else {
                    char buffer2[sizeof(server_join_request_t) + 1];
                    buffer2[0] = SERVER_REQUEST_JOIN;
                    server_join_request_t* jreq = (server_join_request_t*)(buffer2 + 1);
                    jreq->map = state->map;
                    jreq->max_ships_size = state->max_clients;
                    sendto(state->sock, buffer2, sizeof(buffer2), 0,
                        (struct sockaddr*)&client_addr, sizeof(client_addr)
                    );
                }
                printf("%s joined the server\n", req->name);
                }
                break;
            case CLIENT_REQUEST_INPUT: {
                const client_input_request_t* req = (client_input_request_t*)(buffer + 1);
                server_client_t* c = find_server_client_by_addr(state, &client_addr);
                if (c) {
                    c->ship.input_buffer = *req;
                }
                }
                break;
            case CLIENT_REQUEST_CHAT: {
                client_chat_request_t* req = (client_chat_request_t*)(buffer + 1);
                for (size_t i = 0; i < req->size; i++) {
                    if (req->message[i] == '\0') {
                        req->size = i;
                        break;
                    }
                }
                printf("someone said %.*s\n", req->size, req->message);
                }
                break;
            default:
                break;
        }
    }
}

static void korabliki_server(const char* ip) {
    server_state_t state;
    if (!server_setup_socket(ip, &state)) {
        exit(EXIT_FAILURE);
    }
    state.map.width = 1200;
    state.map.height = 600;

    state.clients_size = 0;
    state.max_clients = 12;
    state.clients = malloc(sizeof(server_client_t) * state.max_clients);

    uint8_t* client_ship_data = malloc(sizeof(ship_t) * state.max_clients + 1);
    client_ship_data[0] = SERVER_REQUEST_SHIPS;

    pthread_t tid;
    pthread_create(&tid, NULL, accept_packets_thread, &state);

    bool running = true;
    while (running) {
        for (size_t i = 0; i < state.clients_size; i++) {
            update_ship(&state, &state.clients[i].ship, 1/60.0f);
        }

        for (size_t i = 0; i < state.clients_size; i++) {
            memcpy(client_ship_data + 1 + sizeof(ship_t) * i, &state.clients[i].ship, sizeof(ship_t));
        }

        for (size_t i = 0; i < state.clients_size; i++) {
            sendto(state.sock, client_ship_data, sizeof(ship_t) * state.clients_size + 1, 0, (struct sockaddr*)&state.clients[i].socket, sizeof(struct sockaddr_in));
        }
        usleep(1000000/60);
    }
    pthread_detach(tid);
}
