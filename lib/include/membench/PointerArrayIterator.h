//
// Created by Cedric Courtaud on 23/05/2020.
//

#ifndef MEMBENCH_POINTERARRAYITERATOR_H
#define MEMBENCH_POINTERARRAYITERATOR_H

#include <cstdlib>
#include "macros.h"

namespace membench {
    MB_EXCEPTION(ZeroPointerArraySize, "Pointer array size is 0");


    template<int MLP>
    struct PointerArrayIterator {
        volatile int * array = nullptr;
        volatile int ** p_array = nullptr;
        size_t p_array_size = 0;
        size_t pos = 0;
        size_t n_steps = 0;
        size_t left_interleaving_offset = 0;
        size_t right_interleaving_offset = 0;

        PointerArrayIterator() = default;

        void init(volatile int * array, size_t array_size, size_t n_steps, size_t stride=8,
                  size_t left_interleaving_offset=0, size_t right_interleaving_offset=0) {

            this->left_interleaving_offset = (left_interleaving_offset * stride) / MLP;
            this->right_interleaving_offset = (right_interleaving_offset * stride) / MLP;

            this->array = array;
            this->n_steps = n_steps;

            this->p_array_size = array_size / stride;

            if (this->p_array_size == 0) {
                throw ZeroPointerArraySize();
            }

            this->p_array = new volatile int*[this->p_array_size];

            auto row_offset = 0;
            const auto row_length = array_size / MLP;
            auto col_offset = 0;
            auto step_count = 0;
            for (auto i = 0; i < p_array_size; i++) {
                col_offset %= row_length;
                if ((step_count % n_steps) == 0) {
                    col_offset += this->left_interleaving_offset;
                }

                p_array[i] = &array[row_offset + col_offset];

                row_offset += row_length;
                row_offset %= array_size;

                step_count++;
                step_count %= n_steps;

                if ((step_count % MLP) == 0) {
                    col_offset += stride;
                }

                if (step_count == 0) {
                    col_offset += this->right_interleaving_offset;
                }
            }
        }

        ~PointerArrayIterator() {
            delete this->p_array;
        }
    };
}

#endif //MEMBENCH_POINTERARRAYITERATOR_H
