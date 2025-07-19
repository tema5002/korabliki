#pragma once

static int memeq6(const void* a, const void* b) {
    return !((*(uint64_t*)a ^ *(uint64_t*)b) & 0xFFFFFFFFFFFFULL);
}

static int memeq8(const void* a, const void* b) {
    return !((*(uint64_t*)a ^ *(uint64_t*)b));
}

static int memeq9(const void* a, const void* b) {
    return !((*(uint64_t*)a ^ *(uint64_t*)b) | (((uint8_t*)a)[8] ^ ((uint8_t*)b)[8]));
}

static int memeq16(const void* a, const void* b) {
    return !((*(uint64_t*)a ^ *(uint64_t*)b) | (*(uint64_t*)(a + 8) ^ *(uint64_t*)(b + 8)));
}