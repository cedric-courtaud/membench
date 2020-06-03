//
// Created by Cedric Courtaud on 01/06/2020.
//

#ifndef MEMBENCH_LISTITERATOR_H
#define MEMBENCH_LISTITERATOR_H

#include "macros.h"

namespace membench {
    MB_EXCEPTION(ZeroPointerArraySize, "Pointer array size is 0");

    template<typename T>
    struct ListHead {
        T value;
        ListHead<T> * previous;
        ListHead<T> * next;

        ListHead() {
            previous = this;
            next = this;
        }

        void prepend_to(ListHead<T> * other) {
            next = other;
            other->previous = this;
        }

        void swap_with(ListHead<T> * other) {
            std::swap(other->previous, previous);
            std::swap(other->next, next);
        }
    };

    template<int MLP>
    struct ListIterator {
        volatile int * array = nullptr;
        ListHead<volatile int *> * list_nodes = nullptr;

        size_t p_array_size = 0;
        ListHead<volatile int *> * pos = nullptr;
        size_t n_steps = 0;
        size_t left_interleaving_offset = 0;
        size_t right_interleaving_offset = 0;

        ListIterator() = default;

        void init(volatile int * array, size_t array_size, size_t n_steps, size_t stride=8,
                  size_t left_interleaving_offset=0, size_t right_interleaving_offset=0) {

            this->left_interleaving_offset = (left_interleaving_offset * stride) / MLP;
            this->right_interleaving_offset = (right_interleaving_offset * stride) / MLP;

            this->array = array;
            this->n_steps = n_steps;

            this->p_array_size = array_size / stride;
            this->list_nodes = new ListHead<volatile int *>[p_array_size]();
            this->pos = &list_nodes[0];

            if (this->p_array_size == 0) {
                throw ZeroPointerArraySize();
            }

            auto row_offset = 0;
            const auto row_length = array_size / MLP;
            auto col_offset = 0;
            auto step_count = 0;
            for (auto i = 0; i < p_array_size; i++) {
                col_offset %= row_length;
                if ((step_count % n_steps) == 0) {
                    col_offset += this->left_interleaving_offset;
                }

                list_nodes[i].value = &array[row_offset + col_offset];

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

            for (auto i = 0; i < p_array_size - 1; i++) {
                list_nodes[i].prepend_to(&list_nodes[i + 1]);
            }
            list_nodes[p_array_size - 1].prepend_to(&list_nodes[0]);
        }

        ~ListIterator() {
            delete this->list_nodes;
        }
    };
}


#endif //MEMBENCH_LISTITERATOR_H
