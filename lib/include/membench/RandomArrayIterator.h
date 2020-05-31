//
// Created by Cedric Courtaud on 22/05/2020.
//

#ifndef MEMBENCH_RANDOMARRAYITERATOR_H
#define MEMBENCH_RANDOMARRAYITERATOR_H



#include <cstdlib>

#include "ArrayIterator.h"
#include "lfsr.h"
#include "macros.h"

#define __RANDOM_ARRAY_INDEX(offset, row_length) (offset + (lfsr_rand() % row_length))

namespace membench {
    template <int MLP>
    struct RandomArrayIterator {
        ArrayIterator<MLP> it;

        RandomArrayIterator() = default;

        void init(volatile int * array, size_t array_size, size_t n_steps, size_t stride=8,
                  size_t left_interleaving_offset=0, size_t right_interleaving_offset=0) {
            it.init(array, array_size, n_steps, stride, left_interleaving_offset, right_interleaving_offset);
        }

        FORCE_INLINE int read () {
            auto ret = 0;

            for (auto _ = 0; _ < it.n_steps; _++){
                auto offset = 0;

                SWITCH_MLP(MLP, ({
                    ret += it.array[__RANDOM_ARRAY_INDEX(offset, it.row_length)];
                    offset += it.row_length;
                    asm volatile ("" ::: "memory");
                }), ({
                    ret += it.array[__RANDOM_ARRAY_INDEX(offset, it.row_length)];
                    asm volatile ("" ::: "memory");
                }));
            }

            return ret;
        }

        FORCE_INLINE void write(int value) {
            for (auto _ = 0; _ < it.n_steps; _++){
                auto offset = 0;

                SWITCH_MLP(MLP, ({
                    it.array[__RANDOM_ARRAY_INDEX(offset, it.row_length)] += value;
                    offset += it.row_length;
                    BARRIER;
                }), ({
                    it.array[__RANDOM_ARRAY_INDEX(offset, it.row_length)] += value;
                    BARRIER;
                }));
            }
        }
    };
}

#endif //MEMBENCH_RANDOMARRAYITERATOR_H
