//
// Created by Cedric Courtaud on 21/05/2020.
//

#ifndef MEMBENCHCPP_COMPUTER_H
#define MEMBENCHCPP_COMPUTER_H

#include "macros.h"

namespace membench {
    struct Computer {
        static FORCE_INLINE int compute(int n_step, volatile int value){
            auto v = (unsigned int) value;

            for (int _ = 0; _ < n_step; _++) {
                v = (v << 2u) ^ (0xdeadbeef | v);
            }

            return (int) v;
        }
    };
}

#endif //MEMBENCHCPP_COMPUTER_H
