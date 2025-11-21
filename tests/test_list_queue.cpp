// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_list_queue/list_queue.h"

#define EPSILON 0.000001

TEST(ListQueueTest, ShouldMaintainFIFOOrder) {
    ListQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    EXPECT_EQ(1, queue.front());
    queue.dequeue();
    EXPECT_EQ(2, queue.front());
    queue.dequeue();
    EXPECT_EQ(3, queue.front());
}

TEST(ListQueueTest, ShouldThrowExceptionWhenDequeuingEmptyListQueue) {
    ListQueue<int> queue;
    EXPECT_THROW(queue.dequeue(), std::underflow_error);
    EXPECT_THROW(queue.front(), std::underflow_error);
}

TEST(ListQueueTest, ShouldBeReusableAfterClear) {
    ListQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.clear();

    EXPECT_TRUE(queue.is_empty());
    queue.enqueue(3);
    EXPECT_EQ(3, queue.front());
}

TEST(ListQueueTest, ShouldWrapAroundWhenUsingCircularBuffer) {
    ListQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.dequeue();

    queue.enqueue(4);
    queue.dequeue();
    EXPECT_EQ(3, queue.front());
}

TEST(ListQueueTest, ShouldTrackStatesCorrectly) {
    ListQueue<int> queue;

    EXPECT_TRUE(queue.is_empty());

    queue.enqueue(1);
    EXPECT_FALSE(queue.is_empty());

    queue.enqueue(2);
    queue.enqueue(3);
    EXPECT_FALSE(queue.is_empty());
}

TEST(ListQueueTest, ShouldHandleCircularBufferCorrectly) {
    ListQueue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    queue.dequeue();

    queue.enqueue(4);

    EXPECT_EQ(2, queue.front());
    queue.dequeue();
    EXPECT_EQ(3, queue.front());
    queue.dequeue();
    EXPECT_EQ(4, queue.front());

    EXPECT_FALSE(queue.is_empty());
}
