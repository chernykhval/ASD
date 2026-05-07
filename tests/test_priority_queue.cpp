// Copyright 2026 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_priority_queue/priority_queue.h"

TEST(PriorityQueue, is_empty_on_new_queue) {
    PriorityQueue<int> pq;
    EXPECT_TRUE(pq.is_empty());
}

TEST(PriorityQueue, not_empty_after_push) {
    PriorityQueue<int> pq;
    pq.push(1, 42);
    EXPECT_FALSE(pq.is_empty());
}

TEST(PriorityQueue, empty_after_pop_all) {
    PriorityQueue<int> pq;
    pq.push(1, 10);
    pq.push(2, 20);
    pq.pop();
    pq.pop();
    EXPECT_TRUE(pq.is_empty());
}

TEST(PriorityQueue, pop_returns_min_priority) {
    PriorityQueue<int> pq;
    pq.push(5, 1);
    pq.push(1, 2);
    pq.push(3, 3);
    EXPECT_EQ(pq.pop(), 2);
    EXPECT_EQ(pq.pop(), 3);
    EXPECT_EQ(pq.pop(), 1);
}

TEST(PriorityQueue, top_returns_min_without_removing) {
    PriorityQueue<int> pq;
    pq.push(3, 10);
    pq.push(1, 20);
    EXPECT_EQ(pq.top(), 20);
    EXPECT_EQ(pq.top(), 20);
    EXPECT_FALSE(pq.is_empty());
}

TEST(PriorityQueue, top_priority_returns_min_priority) {
    PriorityQueue<int> pq;
    pq.push(5, 1);
    pq.push(2, 2);
    EXPECT_EQ(pq.top_priority(), 2);
}

TEST(PriorityQueue, equal_priorities_fifo_order) {
    PriorityQueue<int> pq;
    pq.push(1, 10);
    pq.push(1, 20);
    pq.push(1, 30);
    EXPECT_EQ(pq.pop(), 10);
    EXPECT_EQ(pq.pop(), 20);
    EXPECT_EQ(pq.pop(), 30);
}

TEST(PriorityQueue, top_on_empty_throws) {
    PriorityQueue<int> pq;
    EXPECT_THROW(pq.top(), std::logic_error);
}

TEST(PriorityQueue, top_priority_on_empty_throws) {
    PriorityQueue<int> pq;
    EXPECT_THROW(pq.top_priority(), std::logic_error);
}

TEST(PriorityQueue, pop_on_empty_throws) {
    PriorityQueue<int> pq;
    EXPECT_THROW(pq.pop(), std::logic_error);
}

TEST(PriorityQueue, push_after_pop) {
    PriorityQueue<int> pq;
    pq.push(2, 1);
    pq.pop();
    pq.push(1, 99);
    EXPECT_EQ(pq.top(), 99);
}

TEST(PriorityQueue, negative_priority) {
    PriorityQueue<int> pq;
    pq.push(-5, 1);
    pq.push(0, 2);
    pq.push(-10, 3);
    EXPECT_EQ(pq.pop(), 3);
    EXPECT_EQ(pq.pop(), 1);
    EXPECT_EQ(pq.pop(), 2);
}

TEST(PriorityQueue, single_element) {
    PriorityQueue<int> pq;
    pq.push(42, 7);
    EXPECT_EQ(pq.top(), 7);
    EXPECT_EQ(pq.top_priority(), 42);
    EXPECT_EQ(pq.pop(), 7);
    EXPECT_TRUE(pq.is_empty());
}
