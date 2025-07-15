

#include "server_state.h"
#include "../../src/server/ship_logic.h"
#include "../shared/get_sockaddr_in.h"

void* send_thread(void* arg) {
    while (1) {
        server_state_t* state = arg;

        for (int i = 0; i < MAX_PLAYERS; i++) {
            if (state->ships[i].connected) {
                update_ship(state, &state->ships[i], 1.0f/60);
            }
        }

        for (int i = 0; i < MAX_PLAYERS; i++) {
            if (state->ships[i].connected) {
                sendto(state->sock, state->ships, sizeof(state->ships), 0, (struct sockaddr*)&state->addrs[i], sizeof(struct sockaddr_in));
            }
        }
        usleep(1000000/60);
    }
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main(int argc, char* argv[]) {
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        char buffer[MAX(sizeof(ship_input_packet_t), sizeof(register_packet_t))];
        recvfrom(state.sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &addr_len);

        ship_t* player = find_player_by_addr(&state, &client_addr);
        if (player) {
            player->input_buffer = *(ship_input_packet_t*)&buffer;
        }
        else {
            const int id = register_new_player(&state, (register_packet_t*)&buffer, &client_addr);

            registered_packet_t packet;
            packet.id = id;
            if (id != -1) {
                packet.width = state.width;
                packet.height = state.height;
                packet.id = id;
            }
            else {
                packet.id = -1;
            }
            sendto(
                state.sock,
                &packet, sizeof(packet),
                0,
                (struct sockaddr*)&client_addr,
                sizeof(client_addr)
            );

            if (id != -1) {
                printf("new client at %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            }
        }
    }

    close(state.sock);
    return 0;
}
