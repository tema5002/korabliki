#include "includes.h"
#include ".old/server.h"
#include "client/client.h"

int main(const int argc, const char* argv[]) {
    if (argc < 2) {
        fprintf(stderr,
            "usage: %s server [ip]:[port]\n"
            "       %s [ip]:[port] [username]\n",
            argv[0], argv[0]
        );
        return 1;
    }
    const bool is_server = memeq6(argv[1], "server");
    if (is_server) {
        if (argc < 3) {
            fprintf(stderr, "usage: %s server [ip]:[port]\n", argv[0]);
        }
        korabliki_server(argv[2]);
    }
    else {
        korabliki_client(argv[1], argc < 3 ? NULL : argv[2]);
    }

    return 0;
}