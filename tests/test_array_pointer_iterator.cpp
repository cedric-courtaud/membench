//
// Created by Cedric Courtaud on 26/05/2020.
//

#include <gtest/gtest.h>
#include <membench/LinearPointerArrayIterator.h>
#include <membench/RandomPointerArrayIterator.h>

TEST(PointerArrayIterator, LinearPointerArrayIteratorShared) {
volatile int array[4] = {0};
membench::LinearPointerArrayIterator<1> it;

it.init(array, 4, 4, 2);
it.write(1);

ASSERT_EQ(array[0], 2);
ASSERT_EQ(array[1], 0);
ASSERT_EQ(array[2], 2);
ASSERT_EQ(array[3], 0);

int value = it.read();

ASSERT_EQ(value, 8);
}

TEST(PointerArrayIterator, LinearNotShared) {
    volatile int array[4] = {0};
    membench::LinearPointerArrayIterator<1> writer;

    writer.init(array, 4, 4, 2);
    writer.write(1);

    ASSERT_EQ(array[0], 2);
    ASSERT_EQ(array[1], 0);
    ASSERT_EQ(array[2], 2);
    ASSERT_EQ(array[3], 0);


    membench::LinearPointerArrayIterator<1> reader;
    reader.init(array, 4, 2, 2);

    int value = reader.read();

    ASSERT_EQ(value, 4);
}

TEST(PointerArrayIterator, LinearMLPNotShared) {
    volatile int array[16] = {0};
    membench::LinearPointerArrayIterator<4> writer;

    writer.init(array, 16, 4, 1);
    writer.write(1);

    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(array[4], 1);
    ASSERT_EQ(array[8], 1);
    ASSERT_EQ(array[12], 1);

    membench::LinearPointerArrayIterator<1> reader;
    reader.init(array, 16, 4, 4);

    int value = reader.read();

    ASSERT_EQ(value, 4);
}

TEST(PointerArrayIterator, RandomShared) {

    volatile int array[4] = {0};
    membench::RandomPointerArrayIterator<1> it;

    it.init(array, 4, 4, 1);
    it.write(1);

    ASSERT_EQ(array[0] + array [1] + array[2] + array[3], 4);

    auto value = it.read();

    ASSERT_TRUE(value <= 4 * 4);
}

TEST(PointerArrayIterator, RandomArrayIteratorNotShared) {

    volatile int array[4] = {0};
    membench::RandomPointerArrayIterator<1> writer;

    writer.init(array, 4, 4, 1);
    writer.write(1);

    ASSERT_EQ(array[0] + array [1] + array[2] + array[3], 4);

    membench::RandomPointerArrayIterator<1> reader;
    reader.init(array, 4, 4, 1);

    auto value = reader.read();

    ASSERT_TRUE(value <= 4 * 4);
}

TEST(PointerArrayIterator, RandomArrayIteratorMLP) {
    volatile int array[16] = {0};
    membench::RandomPointerArrayIterator<4> writer;

    writer.init(array, 16, 4, 1);
    writer.write(1);

    ASSERT_EQ(array[0]  + array [1]  + array[2]  + array[3],  1);
    ASSERT_EQ(array[4]  + array [5]  + array[6]  + array[7],  1);
    ASSERT_EQ(array[8]  + array [9]  + array[10] + array[11], 1);
    ASSERT_EQ(array[12] + array [13] + array[14] + array[15], 1);

    membench::RandomPointerArrayIterator<4> reader;
    reader.init(array, 16, 4, 1);

    auto value = reader.read();

    ASSERT_TRUE(value <= 4);
}

TEST(PointerArrayIterator, LinearInterleaving1) {
    volatile int array[8] = {0};
    membench::LinearPointerArrayIterator<1> i1;
    membench::LinearPointerArrayIterator<1> i2;
    i1.init(array, 8, 2, 1, 0, 2);
    i2.init(array, 8, 2, 1, 2, 0);

    i1.write(1);
    i2.write(2);
    i1.write(1);
    i2.write(2);

    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(array[1], 1);
    ASSERT_EQ(array[4], 1);
    ASSERT_EQ(array[5], 1);

    ASSERT_EQ(array[2], 2);
    ASSERT_EQ(array[3], 2);
    ASSERT_EQ(array[6], 2);
    ASSERT_EQ(array[7], 2);
}

TEST(PointerArrayIterator, LinearInterleaving2) {
    volatile int array[8] = {0};
    membench::LinearPointerArrayIterator<1> i1;
    membench::LinearPointerArrayIterator<1> i2;
    i1.init(array, 8, 2, 1, 0, 2);
    i2.init(array, 8, 2, 1, 2, 0);

    i1.write(1);
    i1.write(1);

    auto v = i2.read() + i2.read();

    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(array[1], 1);
    ASSERT_EQ(array[4], 1);
    ASSERT_EQ(array[5], 1);

    ASSERT_EQ(v, 0);
}

TEST(PointerArrayIterator, LinearInterleavingMLP1) {
    volatile int array[16] = {0};
    membench::LinearPointerArrayIterator<4> i1;
    membench::LinearPointerArrayIterator<4> i2;
    i1.init(array, 16, 4, 1, 0, 4);
    i2.init(array, 16, 4, 1, 4, 0);

    i1.write(1);
    i2.write(2);
    i1.write(1);
    i2.write(2);

    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(array[4], 1);
    ASSERT_EQ(array[8], 1);
    ASSERT_EQ(array[12], 1);

    ASSERT_EQ(array[1], 2);
    ASSERT_EQ(array[5], 2);
    ASSERT_EQ(array[9], 2);
    ASSERT_EQ(array[13], 2);

    ASSERT_EQ(array[2], 1);
    ASSERT_EQ(array[6], 1);
    ASSERT_EQ(array[10], 1);
    ASSERT_EQ(array[14], 1);

    ASSERT_EQ(array[3], 2);
    ASSERT_EQ(array[7], 2);
    ASSERT_EQ(array[11], 2);
    ASSERT_EQ(array[15], 2);
}

TEST(PointerArrayIterator, LinearInterleavingMLP2) {
    volatile int array[16] = {0};
    membench::LinearPointerArrayIterator<4> i1;
    membench::LinearPointerArrayIterator<4> i2;
    i1.init(array, 16, 4, 1, 0, 4);
    i2.init(array, 16, 4, 1, 4, 0);

    i1.write(1);
    i1.write(1);

    auto v = i2.read() + i2.read();

    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(array[4], 1);
    ASSERT_EQ(array[8], 1);
    ASSERT_EQ(array[12], 1);

    ASSERT_EQ(array[2], 1);
    ASSERT_EQ(array[6], 1);
    ASSERT_EQ(array[10], 1);
    ASSERT_EQ(array[14], 1);

    ASSERT_EQ(v, 0);
}
