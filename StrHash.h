#pragma once
#include <cassert>
#include <cstdint>
#include <string>

class StrHash {
private:
    static constexpr uint64_t _wyp0 = 0xa0761d6478bd642full;
    static constexpr uint64_t _wyp1 = 0xe7037ed1a0b428dbull;
    static constexpr uint64_t _wyp2 = 0x8ebc6af09c88c6e3ull;
    static constexpr uint64_t _wyp3 = 0x589965cc75374cc3ull;
    static constexpr uint64_t _wyp4 = 0x1d8e4e27c47d124full;

    static __forceinline uint64_t mix(uint64_t a, uint64_t b) {
        a ^= b;
        a *= _wyp0;
        a ^= (a >> 32) ^ (a >> 25);
        a *= _wyp1;
        a ^= a >> 33;
        return a;
    }

    static constexpr size_t ct_strlen(const char* str) {
        size_t len = 0;
        while(str[len] != '\0') ++len;
        return len;
    }

    static __forceinline uint64_t load_u64(const char* data, size_t offset) {
        return ((static_cast<uint64_t>(data[offset + 0]) << 0) |
            (static_cast<uint64_t>(data[offset + 1]) << 8) |
            (static_cast<uint64_t>(data[offset + 2]) << 16) |
            (static_cast<uint64_t>(data[offset + 3]) << 24) |
            (static_cast<uint64_t>(data[offset + 4]) << 32) |
            (static_cast<uint64_t>(data[offset + 5]) << 40) |
            (static_cast<uint64_t>(data[offset + 6]) << 48) |
            (static_cast<uint64_t>(data[offset + 7]) << 56));
    }

public:
    static __forceinline uint64_t hash(const char* data, size_t len) {
        assert(data != nullptr && "Data pointer must not be null");
        uint64_t seed = len;

        while(len >= 8) {
            uint64_t k = load_u64(data, 0);
            seed = mix(seed, k);
            data += 8;
            len -= 8;
        }

        uint64_t k = 0;
        switch(len) {
        case 7: k |= uint64_t(data[6]) << 48; [[fallthrough]];
        case 6: k |= uint64_t(data[5]) << 40; [[fallthrough]];
        case 5: k |= uint64_t(data[4]) << 32; [[fallthrough]];
        case 4: k |= uint64_t(data[3]) << 24; [[fallthrough]];
        case 3: k |= uint64_t(data[2]) << 16; [[fallthrough]];
        case 2: k |= uint64_t(data[1]) << 8; [[fallthrough]];
        case 1: k |= uint64_t(data[0]);
        }
        seed = mix(seed, k);

#ifdef _DEBUG
        std::cout << "Hashed data of length " << len << " with result " << seed << std::endl;
#endif

        return seed;
    }

    static __forceinline uint64_t hash(const char* str) {
        return hash(str, ct_strlen(str));
    }

    static uint64_t hash(const std::string& str) {
        return hash(str.data(), str.size());
    }
};

#define HASH(str) []() { constexpr uint64_t out = StrHash::hash(str); return out; }()
#define CONST_HASH(str) StrHash::hash(str)
