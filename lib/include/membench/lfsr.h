//
// Created by Cedric Courtaud on 21/05/2020.
//

#ifndef MEMBENCHCPP_LFSR_H
#define MEMBENCHCPP_LFSR_H

#include <cstdint>

#define LFSR_DEFAULT_SEED 0xbadf00d

uint32_t lfsr = LFSR_DEFAULT_SEED;

static inline void lfsr_srand(uint32_t seed) {
    lfsr = seed;
}

#define MASK 0xd0000001u
#define lfsr_rand() ((lfsr = (lfsr >> 1u) ^ (uint32_t)(0 - (lfsr & 1u) & MASK)))

#endif //MEMBENCHCPP_LFSR_H
