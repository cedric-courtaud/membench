add_library(mbl
        include/membench/macros.h
        include/membench/RCW.h
        include/membench/MemBenchParams.h
        include/membench/Computer.h
        include/membench/LinearArrayIterator.h
        include/membench/ArrayIterator.h
        include/membench/RandomArrayIterator.h
        include/membench/PointerArrayIterator.h
        include/membench/LinearPointerArrayIterator.h
        include/membench/ListIterator.h include/membench/LinearListIterator.h include/membench/RandomListIterator.h
        include/membench/RandomPointerArrayIterator.h
        src/cli.cpp include/membench/cli.h include/membench/ListIterator.h)

target_include_directories(mbl PRIVATE include)
target_include_directories(mbl INTERFACE include)
