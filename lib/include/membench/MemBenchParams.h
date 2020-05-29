//
// Created by Cedric Courtaud on 21/05/2020.
//

#ifndef MEMBENCH_MEMBENCH_PARAMS_H
#define MEMBENCH_MEMBENCH_PARAMS_H

#include <cstdlib>
#include <string>

/*
 *
 * {pattern}-{ds_read}-{ds_write}-{mlp_read}-{mlp_write}-{interleaving}-{read}-{write}-{throttle}
 * {seq-id}-{interleaving}-{read}-{write}-{throttle}
 *
 */

namespace membench {
    struct MemBenchParams {
        int n_read = -1;
        int n_write = -1;
        int throttle = -1;
        std::string access_policy;
        size_t array_size_B = (1u << 20u);
        int memory_fill_value = 1;
        bool interleaved = false; // ignored for now
        size_t stride = 8;
        size_t max_count = 0;
        bool as_load = false;
    };

    class MemBenchInstance {
    public:
        virtual void init(MemBenchParams & p) = 0;
        virtual int run() = 0;
    };
}

#endif
