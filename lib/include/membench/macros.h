//
// Created by Cedric Courtaud on 21/05/2020.
//

#ifndef MEMBENCHCPP_MACROS_H
#define MEMBENCHCPP_MACROS_H
#include <exception>

#define FORCE_INLINE __attribute__((always_inline)) inline

#define SWITCH_MLP(var,expr,last_case_expr) \
    switch (var) { \
        case 32: expr; \
        case 31: expr; \
        case 30: expr; \
        case 29: expr; \
        case 28: expr; \
        case 27: expr; \
        case 26: expr; \
        case 25: expr; \
        case 24: expr; \
        case 23: expr; \
        case 22: expr; \
        case 21: expr; \
        case 20: expr; \
        case 19: expr; \
        case 18: expr; \
        case 17: expr; \
        case 16: expr; \
        case 15: expr; \
        case 14: expr; \
        case 13: expr; \
        case 12: expr; \
        case 11: expr; \
        case 10: expr; \
        case 9: expr; \
        case 8: expr; \
        case 7: expr; \
        case 6: expr; \
        case 5: expr; \
        case 4: expr; \
        case 3: expr; \
        case 2: expr; \
        case 1: last_case_expr; \
        default: break;\
    }

#define BARRIER asm volatile("" ::: "memory")

#define MB_EXCEPTION(type, what_str) class type : public std::exception {\
    const char * what() const noexcept override { return what_str; } \
}

#endif //MEMBENCHCPP_MACROS_H
