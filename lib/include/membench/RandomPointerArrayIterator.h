//
// Created by Cedric Courtaud on 23/05/2020.
//

#ifndef MEMBENCH_RANDOM_POINTERARRAYITERATOR_H
#define MEMBENCH_RANDOM_POINTERARRAYITERATOR_H

#include <cstdlib>
#include <algorithm>
#include <random>
#include "macros.h"
#include "PointerArrayIterator.h"

namespace membench {

    template<typename T>
    void shuffle_array(T * array, size_t array_size) {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0,array_size);

        for (auto i = 0;i < array_size - 1; i++) {
            auto j = i + (distribution(generator) % (array_size - i));
            auto tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
    }

    template<int MLP>
    struct RandomPointerArrayIterator {
        PointerArrayIterator<MLP> it;

        void init(volatile int * array, size_t array_size, size_t n_steps, size_t stride=8) {
            it.init(array, array_size, n_steps, stride);

            for (auto i = 0; i < MLP; i++) {
                auto offset = i * (it.p_array_size / MLP);
                shuffle_array<volatile int *>(&it.p_array[offset], it.p_array_size / MLP);
            }

        }

        FORCE_INLINE int read () {
            auto ret = 0;

            for (auto _ = 0; _ < it.n_steps; _++, it.pos++){
                ret += *it.p_array[it.pos % it.p_array_size];
            }

            BARRIER;

            return ret;
        }

        FORCE_INLINE void write (int value) {
            for (auto _ = 0; _ < it.n_steps; _++, it.pos++){
                *it.p_array[it.pos % it.p_array_size] += value;
            }

            BARRIER;
        }
    };
}

#endif //MEMBENCH_RANDOM_POINTERARRAYITERATOR_H
