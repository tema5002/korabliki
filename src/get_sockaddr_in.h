#pragma once
#include <arpa/inet.h>
#include "memeq.h"

static int parse_ipv4(const char *str, const size_t len, uint32_t* out) {
    if (len < 7 || len > 15) return 0;

    uint32_t ip = 0;
    const char* p = str;
    const char* end = str + len;

    for (int i = 0; i < 4; i++) {
        int val = 0;

        if (p >= end) return 0;
        const char c1 = *p++;
        if (c1 < '0' || c1 > '9') return 0;
        val = c1 - '0';

        if (p < end && *p >= '0' && *p <= '9') {
            const char c2 = *p++;
            val = val * 10 + (c2 - '0');

            if (p < end && *p >= '0' && *p <= '9') {
                const char c3 = *p++;
                val = val * 10 + (c3 - '0');
            }
        }

        if (val > 255) return 0;
        ip = ip << 8 | val;

        if (i < 3) {
            if (p >= end || *p++ != '.') return 0;
        }
    }

    *out = ip;
    return p == end;
}

static int get_sockaddr_in(const char* input, struct sockaddr_in* addr) {
    addr->sin_family = AF_INET;
    const char* port_str = NULL;

    size_t ip_len = 0;
    for (const char* p = input; *p != '\0'; p++, ip_len++) {
        if (*p == ':') {
            port_str = p + 1;
            break;
        }
    }
    if (!port_str) return 0;

    if (ip_len == 9 && memeq9(input, "localhost")) {
        addr->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    }
    else {
        uint32_t ip;
        if (!parse_ipv4(input, ip_len, &ip)) {
            return 0;
        }
        addr->sin_addr.s_addr = htonl(ip);
    }

    uint16_t port = 0;
    while (*port_str >= '0' && *port_str <= '9') {
        port = port * 10 + (*port_str - '0');
        port_str++;
    }

    addr->sin_port = htons(port);
    return 1;
}