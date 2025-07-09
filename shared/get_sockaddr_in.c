#include "get_sockaddr_in.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <bits/socket.h>
#include <netinet/in.h>

struct sockaddr_in get_sockaddr_in(const char* input) {
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

    char buffer[64];
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char* colon = strchr(buffer, ':');
    if (!colon) {
        fprintf(stderr, "format must be IP:PORT\n");
        return addr;
    }

    *colon = '\0';
    const char* ip_str = buffer;
    const char* port_str = colon + 1;

    const int port = atoi(port_str);
    if (port <= 0 || port > UINT16_MAX) {
        fprintf(stderr, "invalid port: %s\n", port_str);
        return addr;
    }

    if (strcmp(ip_str, "localhost") == 0) {
        // keep INADDR_ANY
    }
    else if (inet_pton(AF_INET, ip_str, &addr.sin_addr) != 1) {
        fprintf(stderr, "invalid ip: %s\n", ip_str);
        return addr;
    }

    addr.sin_port = htons(port);
    return addr;
}
