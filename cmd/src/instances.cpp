//
// Created by Cedric Courtaud on 26/05/2020.
//

#include "instances.h"

#include <membench/RCW.h>

#include <membench/Computer.h>
#include <membench/LinearArrayIterator.h>
#include <membench/RandomArrayIterator.h>
#include <membench/LinearPointerArrayIterator.h>
#include <membench/RandomPointerArrayIterator.h>

using namespace membench;

#define __MBI_ENTRY(id, ...) {id, std::make_shared<__VA_ARGS__>()}

std::map<const std::string, std::shared_ptr<MemBenchInstance> > instances = {
        // ARRAY
        __MBI_ENTRY("linear-a-a-1-1",    RCW<LinearArrayIterator<1>, Computer, LinearArrayIterator<1>>),
        __MBI_ENTRY("random-a-a-1-1",    RCW<RandomArrayIterator<1>, Computer, RandomArrayIterator<1>>),
        __MBI_ENTRY("gather-a-a-1-1",    RCW<RandomArrayIterator<1>, Computer, LinearArrayIterator<1>>),
        __MBI_ENTRY("scatter-a-a-1-1",   RCW<LinearArrayIterator<1>, Computer, RandomArrayIterator<1>>),
        // POINTER ARRAY
        __MBI_ENTRY("linear-p-p-1-1",    RCW<LinearPointerArrayIterator<1>, Computer, LinearPointerArrayIterator<1>>),
        __MBI_ENTRY("random-p-p-1-1",    RCW<RandomPointerArrayIterator<1>, Computer, RandomPointerArrayIterator<1>>),
        __MBI_ENTRY("gather-p-p-1-1",    RCW<RandomPointerArrayIterator<1>, Computer, LinearPointerArrayIterator<1>>),
        __MBI_ENTRY("scatter-p-p-1-1",   RCW<LinearPointerArrayIterator<1>, Computer, RandomPointerArrayIterator<1>>),

        // Stream generalizations
        // --- parallel arrays read / single array write
        __MBI_ENTRY("linear-a-a-2-1",    RCW<LinearArrayIterator<2>, Computer, LinearArrayIterator<1>>),
        __MBI_ENTRY("linear-a-a-4-1",    RCW<LinearArrayIterator<4>, Computer, LinearArrayIterator<1>>),
        __MBI_ENTRY("linear-a-a-8-1",    RCW<LinearArrayIterator<8>, Computer, LinearArrayIterator<1>>),
        __MBI_ENTRY("linear-a-a-16-1",   RCW<LinearArrayIterator<16>, Computer, LinearArrayIterator<1>>),
        __MBI_ENTRY("linear-a-a-32-1",   RCW<LinearArrayIterator<32>, Computer, LinearArrayIterator<1>>),
        // --- single array read / parallel arrays write
        __MBI_ENTRY("linear-a-a-1-2",    RCW<LinearArrayIterator<1>, Computer, LinearArrayIterator<2>>),
        __MBI_ENTRY("linear-a-a-1-4",    RCW<LinearArrayIterator<1>, Computer, LinearArrayIterator<4>>),
        __MBI_ENTRY("linear-a-a-1-8",    RCW<LinearArrayIterator<1>, Computer, LinearArrayIterator<8>>),
        __MBI_ENTRY("linear-a-a-1-16",   RCW<LinearArrayIterator<1>, Computer, LinearArrayIterator<16>>),
        __MBI_ENTRY("linear-a-a-1-32",   RCW<LinearArrayIterator<1>, Computer, LinearArrayIterator<32>>),
        // --- symmetric
        __MBI_ENTRY("linear-a-a-2-2",    RCW<LinearArrayIterator<2>, Computer, LinearArrayIterator<2>>),
        __MBI_ENTRY("linear-a-a-4-4",    RCW<LinearArrayIterator<4>, Computer, LinearArrayIterator<4>>),
        __MBI_ENTRY("linear-a-a-8-8",    RCW<LinearArrayIterator<8>, Computer, LinearArrayIterator<8>>),
        __MBI_ENTRY("linear-a-a-16-16",  RCW<LinearArrayIterator<16>, Computer, LinearArrayIterator<16>>),
        __MBI_ENTRY("linear-a-a-32-32",  RCW<LinearArrayIterator<32>, Computer, LinearArrayIterator<32>>),
};

