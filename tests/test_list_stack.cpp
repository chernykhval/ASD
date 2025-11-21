// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_list_stack/list_stack.h"

#define EPSILON 0.000001

TEST(ListStackTest, CreateIndependentCopyByOriginalModifications) {
    ListStack<int> original_stack;

    for (int i = 0; i < 3; i++) {
        original_stack.push(i);
    }

    ListStack<int> copy_stack(original_stack);

    original_stack.pop();
    original_stack.push(100);
    EXPECT_EQ(2, copy_stack.top());
}

TEST(ListStackTest, TransitionBetweenEmptyFullStatesDuringPushPopOperations) {
    ListStack<int> stack;

    EXPECT_TRUE(stack.is_empty());

    stack.push(100);

    EXPECT_FALSE(stack.is_empty());

    for (int i = 0; i < 5; i++) {
        stack.push(i);
    }

    EXPECT_FALSE(stack.is_empty());

    stack.pop();

    EXPECT_FALSE(stack.is_empty());

    for (int i = 0; i < 5; i++) {
        stack.pop();
    }

    EXPECT_TRUE(stack.is_empty());
}

TEST(ListStackTest, PopEmptyListStackWithException) {
    ListStack<int> stack;

    EXPECT_THROW(stack.pop(), std::underflow_error);
    EXPECT_TRUE(stack.is_empty());
}

TEST(ListStackTest, ShouldAllowModifyingTopElementThroughReference) {
    ListStack<int> stack;
    stack.push(100);

    stack.top() = 200;
    EXPECT_EQ(stack.top(), 200);

    int& top_ref = stack.top();
    top_ref = 300;
    EXPECT_EQ(stack.top(), 300);
}

TEST(ListStackTest, ShouldReturnCopyThatDoesNotAffectListStackWhenModified) {
    ListStack<int> stack;

    stack.push(100);

    int value = stack.top();

    EXPECT_EQ(value, 100);

    value = 23;

    EXPECT_EQ(stack.top(), 100);
}

TEST(ListStackTest, ShouldResetListStackToEmptyStateAfterClear) {
    ListStack<int> stack;

    for (int i = 0; i < 5; i++) {
        stack.push(i);
    }

    stack.clear();

    EXPECT_TRUE(stack.is_empty());

    stack.push(100);

    EXPECT_EQ(100, stack.top());
    EXPECT_FALSE(stack.is_empty());
}
