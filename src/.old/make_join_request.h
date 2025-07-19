#pragma once

static void make_join_request(const char* name, const client_state_t* state, client_join_request_t* request) {
    if (name) {
        strncpy(request->name, name, sizeof(request->name));
        return;
    }

    const struct passwd* pw = getpwuid(getuid());
    if (pw) {
        strncpy(request->name, pw->pw_name, sizeof(request->name) - 1);
        request->name[sizeof(request->name) - 1] = '\0';
    }
    else {
        struct sockaddr_in self_addr;
        socklen_t len = sizeof(self_addr);
        getsockname(state->sock, (struct sockaddr*)&self_addr, &len);
        snprintf(request->name, sizeof(request->name), "%s:%d", inet_ntoa(self_addr.sin_addr), ntohs(self_addr.sin_port));
    }
}