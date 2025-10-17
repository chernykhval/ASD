// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_QUEUE_QUEUE_H_
#define LIBS_LIB_QUEUE_QUEUE_H_

#include <stdexcept>

template<typename T>
class Queue {
 private:
    T* _data;
    size_t _size, _front, _count;

 public:
    explicit Queue(size_t size = 1);
    Queue(const Queue& other);
    ~Queue() noexcept;

    void enqueue(const T& value);
    void dequeue();
    T& front();
    bool is_empty() const noexcept;
    bool is_full() const noexcept;
    void clear() noexcept;
};

#endif  // LIBS_LIB_QUEUE_QUEUE_H_
