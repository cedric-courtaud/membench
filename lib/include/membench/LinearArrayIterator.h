#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
//
// Created by Cedric Courtaud on 22/05/2020.
//

#ifndef MEMBENCH_ARRAY_H
#define MEMBENCH_ARRAY_H

#include <cstdlib>
#include "macros.h"

#include "ArrayIterator.h"

namespace membench {
    template <int MLP>
    struct LinearArrayIterator {
        ArrayIterator<MLP> it;

        LinearArrayIterator() = default;

        void init(volatile int * array, size_t array_size, size_t n_steps, size_t stride=8) {
            it.init(array, array_size, n_steps, stride);
        }

        FORCE_INLINE int read () {
            auto ret = 0;

            for (auto _ = 0; _ < it.n_steps; _++){
                auto offset = 0;

                SWITCH_MLP(MLP, ({
                    ret += it.array[offset + it.pos];
                    offset += it.row_length;
                    BARRIER;
                }), ({
                    ret += it.array[offset + it.pos];
                    BARRIER;
                }));

                it.pos = (it.pos + it.stride) % it.row_length;
            }

            return ret;
        }

        FORCE_INLINE void write(int value) {
            for (auto _ = 0; _ < it.n_steps; _++){
                auto offset = 0;

                SWITCH_MLP(MLP, ({
                    it.array[offset + it.pos] += value;
                    offset += it.row_length;
                    BARRIER;
                }), ({
                    it.array[offset + it.pos] += value;
                    BARRIER;
                }));

                it.pos = (it.pos + it.stride) % it.row_length;
            }
        }
    };
}

#endif //MEMBENCH_ARRAY_H

#pragma clang diagnostic pop