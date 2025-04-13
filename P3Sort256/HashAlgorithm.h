#pragma once

#include "pch.h"


// If you are curious as to what I did, how this works, or are interested in learning about this after the project: https://en.wikipedia.org/wiki/SHA-2 

class HashAlgorithm
{
private:
    static inline uint32_t ROTR(uint32_t x, uint32_t n) {
        return (x >> n) | (x << (32 - n));
    }
    static inline uint32_t CH(uint32_t x, uint32_t y, uint32_t z) {
        return (x & y) ^ (~x & z);
    }
    static inline uint32_t MAJ(uint32_t x, uint32_t y, uint32_t z) {
        return (x & y) ^ (x & z) ^ (y & z);
    }
    static inline uint32_t SIGMA0(uint32_t x) {
        return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22);
    }
    static inline uint32_t SIGMA1(uint32_t x) {
        return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25);
    }
    static inline uint32_t sigma0(uint32_t x) {
        return ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3);
    }
    static inline uint32_t sigma1(uint32_t x) {
        return ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10);
    }

public:
    static void hash(std::string& input);
    std::vector<int> convertInputToHash(std::vector<std::pair<std::string, std::string>>& givenDataSet);
};

