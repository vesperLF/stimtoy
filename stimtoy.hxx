#ifndef STIMTOY
#define STIMTOY

#include <array>
#include <bitset>

// https://archiveofourown.org/works/58671715/chapters/167421601
union stimtoy {
    // boolean
    std::bitset<8192> b;

    // integer
    std::array<uint8_t, 1024> u8;
    std::array<uint16_t, 512> u16;
    std::array<uint32_t, 256> u32;
    std::array<uint64_t, 128> u64;
    std::array<int8_t, 1024> i8;
    std::array<int16_t, 512> i16;
    std::array<int32_t, 256> i32;
    std::array<int64_t, 128> i64;

    // floating point
    std::array<float, 256> fp32;
    std::array<double, 128> fp64;

    // character
    std::array<char8_t, 1024> c8;
    std::array<char16_t, 512> c16;
    std::array<char32_t, 256> c32;

    // xoshiro256++ state
    std::array<std::array<uint64_t, 4>, 32> xoshiro_state;


    stimtoy() {
        u8 = {};
    }

    // "I held the leading four bytes of the block of memory, interpreted it as a number, and repeatedly alternated between multiplying it by 1,664,525 and adding 101,3904,223 for a satisfying pseudorandom walk through the entire sequence."
    void sallys_first_stim() {
        u32[0] *= 1664525;
        u32[0] += 1013904223;
    }

private:
    static inline uint64_t rotl(uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }
public:

    // https://prng.di.unimi.it/
    uint64_t xoshiro_stim(size_t i) {
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
};

#endif /* STIMTOY */
