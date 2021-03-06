//
// Created by Cedric Courtaud on 22/05/2020.
//

#ifndef MEMBENCH_ARRAYITERATOR_H
#define MEMBENCH_ARRAYITERATOR_H

#include <cstdlib>

namespace membench {
    template <int MLP>
    struct ArrayIterator {
        volatile int * array = nullptr;
        size_t pos = 0;
        size_t n_steps = 0;
        size_t row_length = 0;
        size_t stride = 0;
        size_t left_interleaving_offset = 0;
        size_t right_interleaving_offset = 0;

        ArrayIterator() = default;

        void init(volatile int * array, size_t array_size, size_t n_steps, size_t stride=8,
                  size_t left_interleaving_offset=0, size_t right_interleaving_offset=0) {

            this->left_interleaving_offset = (left_interleaving_offset * stride) / MLP;
            this->right_interleaving_offset = (right_interleaving_offset * stride) / MLP;
            this->n_steps = n_steps;
            this->stride = stride;
            this->row_length = array_size / MLP;
            this->array = array;
        }

    };
}

#endif //MEMBENCH_ARRAYITERATOR_H
