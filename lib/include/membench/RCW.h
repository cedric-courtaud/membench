//
// Created by Cedric Courtaud on 21/05/2020.
//

#ifndef MEMBENCH_RCW_H
#define MEMBENCH_RCW_H


#include <cstddef>
#include "macros.h"
#include "MemBenchParams.h"

namespace membench {
    MB_EXCEPTION(DifferentMLPInterleavingException, "Trying to interleave two iterator with different MLP value");


    template<class Reader, class Computer, class Writer>
    class RCW : public MemBenchInstance {
        size_t max_count = 0;
        bool as_load = false;
        unsigned int n_compute = 0;

        Reader reader;
        Computer computer;
        Writer writer;

    public:
        RCW() = default;
        volatile int * memory = nullptr;

        void init(MemBenchParams & p) override {
            // Initialize memory
            size_t array_size = p.array_size_B / sizeof(*memory);
            memory = (typeof memory) malloc(p.array_size_B);

            if (!memory) {
                perror("RCW malloc");
                exit(EXIT_FAILURE);
            }

            std::fill_n(memory, array_size, p.memory_fill_value);

            // INIT READER AND WRITER
            if (p.interleaved) {
                if (reader.mlp != writer.mlp) {
                    throw DifferentMLPInterleavingException();
                }
                reader.init(memory, array_size, p.n_read,  p.stride, 0, p.n_write);
                writer.init(memory, array_size, p.n_write, p.stride, p.n_read, 0);
            } else {
                auto s = array_size / 2;

                reader.init(memory, s, p.n_read, p.stride,  0, 0);
                writer.init(memory + s, s, p.n_write, p.stride, 0, 0);
            }

            // INIT COMPUTER
            n_compute = p.throttle * (p.n_read + p.n_write);

            // ITERATION COUNT
            max_count = (p.max_count == 0) ? (array_size / p.stride) : p.max_count;
            as_load = p.as_load;
        }

        int __run() {
            int ret = 0;

            for (auto _ = 0; _ < max_count; _ += reader.it.n_steps + writer.it.n_steps) {
                ret += reader.read();

                ret = computer.compute(n_compute, ret);

                writer.write(ret);
            }

            return ret;
        }

        int run() override {
            if (this->as_load) {
                while (true) __run();
            }

            return __run();
        }

        virtual ~RCW() {
            free((void *) memory);
        }
    };
}


#endif //MEMBENCHCPP_RCW_H
