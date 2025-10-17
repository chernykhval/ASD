// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_queue/queue.h"

#define EPSILON 0.000001

TEST(QueueTest, ShouldMaintainFIFOOrder) {
    Queue<int> queue(3);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    EXPECT_EQ(1, queue.front());
    queue.dequeue();
    EXPECT_EQ(2, queue.front());
    queue.dequeue();
    EXPECT_EQ(3, queue.front());
}

TEST(QueueTest, ShouldThrowExceptionWhenEnqueuingToFullQueue) {
    Queue<int> queue(2);
    queue.enqueue(1);
    queue.enqueue(2);

    EXPECT_THROW(queue.enqueue(3), std::overflow_error);
    EXPECT_TRUE(queue.is_full());
}

TEST(QueueTest, ShouldThrowExceptionWhenDequeuingEmptyQueue) {
    Queue<int> queue(3);
    EXPECT_THROW(queue.dequeue(), std::underflow_error);
    EXPECT_THROW(queue.front(), std::underflow_error);
}

TEST(QueueTest, ShouldBeReusableAfterClear) {
    Queue<int> queue(3);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.clear();

    EXPECT_TRUE(queue.is_empty());
    queue.enqueue(3);
    EXPECT_EQ(3, queue.front());
}

TEST(QueueTest, ShouldWrapAroundWhenUsingCircularBuffer) {
    Queue<int> queue(3);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.dequeue();

    queue.enqueue(4);
    queue.dequeue();
    EXPECT_EQ(3, queue.front());
}

TEST(QueueTest, ShouldTrackStatesCorrectly) {
    Queue<int> queue(3);

    EXPECT_TRUE(queue.is_empty());
    EXPECT_FALSE(queue.is_full());

    queue.enqueue(1);
    EXPECT_FALSE(queue.is_empty());
    EXPECT_FALSE(queue.is_full());

    queue.enqueue(2);
    queue.enqueue(3);
    EXPECT_FALSE(queue.is_empty());
    EXPECT_TRUE(queue.is_full());
}
