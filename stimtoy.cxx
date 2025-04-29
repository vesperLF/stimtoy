#include "stimtoy.hxx"

void stimtoy::sallys_first_stim() {
    u32[0] *= 1664525;
    u32[0] += 1013904223;
}

static inline uint64_t rotl(uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

// https://prng.di.unimi.it/
uint64_t stimtoy::xoshiro_stim(size_t i) {
    std::array<uint64_t, 4>& s = xoshiro_state[i];
    const uint64_t result = rotl(s[0] + s[3], 23) + s[0];

    const uint64_t t = s[1] << 17;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];
    s[2] ^= t;
    s[3] = rotl(s[3], 45);

    return result;
}
