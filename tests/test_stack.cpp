// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_stack/stack.h"

#define EPSILON 0.000001

TEST(StackTest, ShouldThrowExceptionWhenCreatingStackWithZeroSize) {
    EXPECT_THROW(Stack<int> stack(0), std::invalid_argument);
}

TEST(StackTest, ShouldCreateIndependentCopyUnaffectedByOriginalModifications) {
    Stack<int> original_stack(5);

    for (int i = 0; i < 3; i++) {
        original_stack.push(i);
    }

    Stack<int> copy_stack(original_stack);

    original_stack.pop();
    original_stack.push(100);
    EXPECT_EQ(2, copy_stack.top());
}

TEST(StackTest, ShouldPreventOverflowByThrowingException) {
    size_t size = 5;
    Stack<int> stack(size);

    for (int i = 0; i < size; i++) {
        stack.push(i);
    }

    EXPECT_THROW(stack.push(100), std::overflow_error);
    EXPECT_TRUE(stack.is_full());
    EXPECT_FALSE(stack.is_empty());
}

TEST(StackTest, ShouldTransitionBetweenEmptyFullStatesDuringPushPopOperations) {
    size_t size = 5;
    Stack<int> stack(size);

    EXPECT_FALSE(stack.is_full());
    EXPECT_TRUE(stack.is_empty());

    stack.push(100);

    EXPECT_FALSE(stack.is_full());
    EXPECT_FALSE(stack.is_empty());

    for (int i = 0; i < size - 1; i++) {
        stack.push(i);
    }

    EXPECT_TRUE(stack.is_full());
    EXPECT_FALSE(stack.is_empty());

    stack.pop();

    EXPECT_FALSE(stack.is_full());
    EXPECT_FALSE(stack.is_empty());

    for (int i = 0; i < size - 1; i++) {
        stack.pop();
    }

    EXPECT_FALSE(stack.is_full());
    EXPECT_TRUE(stack.is_empty());
}

TEST(StackTest, PopEmptyStackWithException) {
    int size = 1;
    Stack<int> stack(size);

    EXPECT_THROW(stack.pop(), std::underflow_error);
    EXPECT_FALSE(stack.is_full());
    EXPECT_TRUE(stack.is_empty());
}

TEST(StackTest, ShouldAllowModifyingTopElementThroughReference) {
    Stack<int> stack(5);
    stack.push(100);

    stack.top() = 200;
    EXPECT_EQ(stack.top(), 200);

    int& top_ref = stack.top();
    top_ref = 300;
    EXPECT_EQ(stack.top(), 300);
}

TEST(StackTest, ShouldReturnCopyThatDoesNotAffectStackWhenModified) {
    int size = 5;
    Stack<int> stack(size);

    stack.push(100);

    int value = stack.top();

    EXPECT_EQ(value, 100);

    value = 23;

    EXPECT_EQ(stack.top(), 100);
}

TEST(StackTest, ShouldResetStackToEmptyStateAfterClear) {
    int size = 5;
    Stack<int> stack(size);

    for (int i = 0; i < size - 2; i++) {
        stack.push(i);
    }

    stack.clear();

    EXPECT_FALSE(stack.is_full());
    EXPECT_TRUE(stack.is_empty());

    stack.push(100);

    EXPECT_EQ(100, stack.top());
    EXPECT_FALSE(stack.is_empty());
}
