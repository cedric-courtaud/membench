//
// Created by Cedric Courtaud on 30/05/2020.
//

#include <gtest/gtest.h>
#include <membench/RCW.h>
#include <membench/MemBenchParams.h>
#include <membench/LinearArrayIterator.h>
#include <membench/Computer.h>
#include <membench/RandomArrayIterator.h>
#include <membench/RandomPointerArrayIterator.h>
#include <membench/LinearPointerArrayIterator.h>

TEST(RCW, NoInterleaving) {
    membench::MemBenchParams p = {
            .n_read = 1,
            .n_write = 1,
            .throttle = 0,
            .array_size_B = 8 * sizeof(int),
            .memory_fill_value = 1,
            .interleaved = false,
            .stride = 1,
            .max_count = 8,
            .as_load = false
    };

    membench::RCW<membench::LinearArrayIterator<1>, membench::Computer, membench::LinearArrayIterator<1>> t;

    t.init(p);
    t.run();

    ASSERT_EQ(t.memory[0], 1);
    ASSERT_EQ(t.memory[1], 1);
    ASSERT_EQ(t.memory[2], 1);
    ASSERT_EQ(t.memory[3], 1);
    ASSERT_EQ(t.memory[4], 2);
    ASSERT_EQ(t.memory[5], 3);
    ASSERT_EQ(t.memory[6], 4);
    ASSERT_EQ(t.memory[7], 5);
}

TEST(RCW, Interleaving) {
    membench::MemBenchParams p = {
            .n_read = 1,
            .n_write = 1,
            .throttle = 0,
            .array_size_B = 8 * sizeof(int),
            .memory_fill_value = 1,
            .interleaved = true,
            .stride = 1,
            .max_count = 8,
            .as_load = false
    };

    membench::RCW<membench::LinearArrayIterator<1>, membench::Computer, membench::LinearArrayIterator<1>> t;

    t.init(p);
    t.run();

    ASSERT_EQ(t.memory[0], 1);
    ASSERT_EQ(t.memory[1], 2);
    ASSERT_EQ(t.memory[2], 1);
    ASSERT_EQ(t.memory[3], 3);
    ASSERT_EQ(t.memory[4], 1);
    ASSERT_EQ(t.memory[5], 4);
    ASSERT_EQ(t.memory[6], 1);
    ASSERT_EQ(t.memory[7], 5);
}


TEST(RCW, InterleavingDifferentMLPException) {
    membench::MemBenchParams p = {
            .n_read = 1,
            .n_write = 1,
            .throttle = 0,
            .array_size_B = 8 * sizeof(int),
            .memory_fill_value = 1,
            .interleaved = true,
            .stride = 1,
            .max_count = 8,
            .as_load = false
    };

    membench::RCW<membench::LinearArrayIterator<4>, membench::Computer, membench::LinearArrayIterator<1>> t;
    ASSERT_THROW(t.init(p), membench::DifferentMLPInterleavingException);

    membench::RCW<membench::RandomArrayIterator<4>, membench::Computer, membench::LinearArrayIterator<1>> t1;
    ASSERT_THROW(t1.init(p), membench::DifferentMLPInterleavingException);

    membench::RCW<membench::RandomPointerArrayIterator<4>, membench::Computer, membench::LinearArrayIterator<1>> t2;
    ASSERT_THROW(t2.init(p), membench::DifferentMLPInterleavingException);

    membench::RCW<membench::LinearPointerArrayIterator<4>, membench::Computer, membench::LinearArrayIterator<1>> t3;
    ASSERT_THROW(t3.init(p), membench::DifferentMLPInterleavingException);
}

