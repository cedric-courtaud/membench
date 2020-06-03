//
// Created by Cedric Courtaud on 23/05/2020.
//

#ifndef MEMBENCH_RANDOMLISTITERATOR_H
#define MEMBENCH_RANDOMLISTITERATOR_H

#include <cstdlib>
#include <random>
#include "macros.h"
#include "ListIterator.h"

namespace membench {
    template<int MLP>
    struct RandomListIterator {
        ListIterator<MLP> it;
        static constexpr int mlp = MLP;

        template<typename T>
        void shuffle_lists_nodes(ListHead<T> * array, size_t array_size) {
            std::default_random_engine generator;
            std::uniform_int_distribution<int> distribution(0,array_size);

            auto row_length = array_size / MLP;

            for (auto i=0; i < row_length - 1; i++) {
                for (auto m=1; m <= mlp; m++) {
                    auto j = i + (distribution(generator) % (row_length - i));
                    array[i].swapWith(&array[m*j]);
                }
            }
        }

        void init(volatile int * array, size_t array_size, size_t n_steps, size_t stride=8,
                  size_t left_interleaving_offset=0, size_t right_interleaving_offset=0) {
            it.init(array, array_size, n_steps, stride, left_interleaving_offset, right_interleaving_offset);
        }

        FORCE_INLINE int read () {
            auto ret = 0;

            for (auto _ = 0; _ < it.n_steps; _++){
                ret += *it.pos->value;
                it.pos = it.pos->next;
                BARRIER;
            }


            return ret;
        }

        FORCE_INLINE void write (int value) {
            for (auto _ = 0; _ < it.n_steps; _++){
                *it.pos->value += value;
                it.pos = it.pos->next;
                BARRIER;
            }
        }
    };
}

#endif //MEMBENCH_LINEARPOINTERARRAYITERATOR_H
