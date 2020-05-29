//
// Created by Cedric Courtaud on 26/05/2020.
//

#include <gtest/gtest.h>
#include <membench/LinearPointerArrayIterator.h>
#include <membench/RandomPointerArrayIterator.h>

TEST(ArrayIterator, LinearPointerArrayIteratorShared) {
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