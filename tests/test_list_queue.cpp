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

TEST(TestListQueue, CopyConstructor) {
    // Создаем и заполняем исходную очередь
    ListQueue<int> original;
    original.enqueue(1);
    original.enqueue(2);
    original.enqueue(3);

    // Создаем копию через конструктор копирования
    ListQueue<int> copy_queue(original);

    // Проверяем, что копия содержит те же элементы
    EXPECT_EQ(copy_queue.front(), 1);
    copy_queue.dequeue();
    EXPECT_EQ(copy_queue.front(), 2);
    copy_queue.dequeue();
    EXPECT_EQ(copy_queue.front(), 3);

    // Проверяем, что исходная очередь не изменилась
    EXPECT_EQ(original.front(), 1);
    original.dequeue();
    EXPECT_EQ(original.front(), 2);
    original.dequeue();
    EXPECT_EQ(original.front(), 3);
    original.dequeue();
    EXPECT_TRUE(original.is_empty());
}

TEST(TestListQueue, CopyConstructorDeepCopy) {
    // Создаем исходную очередь
    ListQueue<int> original;
    original.enqueue(1);
    original.enqueue(2);
    original.enqueue(3);

    // Создаем две независимые копии
    ListQueue<int> copy1(original);
    ListQueue<int> copy2(original);

    // Модифицируем первую копию
    copy1.enqueue(4);

    // Модифицируем вторую копию
    copy2.enqueue(5);
    copy2.enqueue(6);

    // Проверяем, что изменения в копиях независимы
    EXPECT_EQ(copy1.front(), 1);
    copy1.dequeue();
    EXPECT_EQ(copy1.front(), 2);
    copy1.dequeue();
    EXPECT_EQ(copy1.front(), 3);
    copy1.dequeue();
    EXPECT_EQ(copy1.front(), 4);
    copy1.dequeue();
    EXPECT_TRUE(copy1.is_empty());

    EXPECT_EQ(copy2.front(), 1);
    copy2.dequeue();
    EXPECT_EQ(copy2.front(), 2);
    copy2.dequeue();
    EXPECT_EQ(copy2.front(), 3);
    copy2.dequeue();
    EXPECT_EQ(copy2.front(), 5);
    copy2.dequeue();
    EXPECT_EQ(copy2.front(), 6);
    copy2.dequeue();
    EXPECT_TRUE(copy2.is_empty());

    // Проверяем, что исходная очередь не изменилась
    EXPECT_EQ(original.front(), 1);
    original.dequeue();
    EXPECT_EQ(original.front(), 2);
    original.dequeue();
    EXPECT_EQ(original.front(), 3);
    original.dequeue();
    EXPECT_TRUE(original.is_empty());
}
