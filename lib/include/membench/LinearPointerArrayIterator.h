//
// Created by Cedric Courtaud on 23/05/2020.
//

#ifndef MEMBENCH_LINEARPOINTERARRAYITERATOR_H
#define MEMBENCH_LINEARPOINTERARRAYITERATOR_H

#include <cstdlib>
#include "macros.h"
#include "PointerArrayIterator.h"

namespace membench {
    template<int MLP>
    struct LinearPointerArrayIterator {
        PointerArrayIterator<MLP> it;

        void init(volatile int * array, size_t array_size, size_t n_steps, size_t stride=8) {
            it.init(array, array_size, n_steps, stride);
        }

        FORCE_INLINE int read () {
            auto ret = 0;

            for (auto _ = 0; _ < it.n_steps; _++, it.pos++){
                ret += *it.p_array[it.pos % it.p_array_size];
                BARRIER;
            }


            return ret;
        }

        FORCE_INLINE void write (int value) {
            for (auto _ = 0; _ < it.n_steps; _++, it.pos++){
                *it.p_array[it.pos % it.p_array_size] += value;
                BARRIER;
            }
        }
    };
}

#endif //MEMBENCH_LINEARPOINTERARRAYITERATOR_H
