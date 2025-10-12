// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_stack/stack.h"

#define EPSILON 0.000001

TEST(StackTest, size_init) {
    Stack<int> stack_1(5);

    for (int i = 0; i < 6; i++) {
        stack_1.push(i);

        if (i == 5) {
            EXPECT_ANY_THROW(stack_1.push(i));
        }
    }

    EXPECT_ANY_THROW(Stack<int> stack_2(0));
}

TEST(StackTest, copy_init) {
    Stack<int> stack_1(5);

    for (int i = 0; i < 3; i++) {
        stack_1.push(i);
    }

    Stack<int> stack_2(stack_1);

    for (int i = 0; i < 3; i++) {
        stack_2.push(i);

        if (i == 2) {
            EXPECT_ANY_THROW(stack_2.push(i));
        }
    }
}

TEST(StackTest, push) {
}

TEST(StackTest, pop) {
}

TEST(StackTest, top) {
}

TEST(StackTest, const_top) {
}

TEST(StackTest, copy_top) {
}

TEST(StackTest, is_empty) {
}

TEST(StackTest, is_full) {
}

TEST(StackTest, clear) {
}
