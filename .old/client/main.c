#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>

#include "../../src/client/ship_renderer.h"
#include "window.h"
#include "../../src/client/font.h"
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

int main(int argc, char* argv[]) {
    while (running) {



    }
    return 0;
}
