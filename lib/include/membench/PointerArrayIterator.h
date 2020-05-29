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

        PointerArrayIterator() = default;

        void init(volatile int * array, size_t array_size, size_t n_steps, size_t stride=8) {
            this->array = array;
            this->n_steps = n_steps;

            this->p_array_size = array_size / stride;

            if (this->p_array_size == 0) {
                throw ZeroPointerArraySize();
            }

            this->p_array = new volatile int*[this->p_array_size];

            for (auto i = 0; i < array_size; i += stride) {
                auto col_offset = (i % MLP) * MLP;
                auto row_offset = i / MLP / stride;
                p_array[col_offset + row_offset] = &array[i];
            }
        }

        ~PointerArrayIterator() {
            delete this->p_array;
        }
    };
}

#endif //MEMBENCH_POINTERARRAYITERATOR_H
