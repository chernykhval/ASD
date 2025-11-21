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

template<typename T>
Queue<T>::Queue(size_t size) {
    if (size == 0) {
        throw std::invalid_argument("Stack size cannot be 0");
    }

    _data = new T[size];
    _front = 0;
    _count = 0;
    _size = size;
}

template<typename T>
Queue<T>::Queue(const Queue& other) : _size(other._size),
_front(other._front), _count(other._count) {
    _data = new T[_size];

    for (size_t i = 0; i < _count; i++) {
        size_t src_index = (other._front + i) % other._size;
        _data[i] = other._data[src_index];
    }
}

template<typename T>
Queue<T>::~Queue() noexcept {
    delete[] _data;
}

template<typename T>
void Queue<T>::enqueue(const T& value) {
    if (is_full()) {
        throw std::overflow_error("Queue is full");
    }

    size_t next_index = (_front + _count) % _size;
    _data[next_index] = value;
    _count++;
}

template<typename T>
void Queue<T>::dequeue() {
    if (is_empty()) {
        throw std::underflow_error("Queue is empty");
    }

    _front = (_front + 1) % _size;
    _count--;
}

template<typename T>
T & Queue<T>::front() {
    if (is_empty()) {
        throw std::underflow_error("Queue is empty");
    }

    return _data[_front];
}

template<typename T>
bool Queue<T>::is_empty() const noexcept {
    return _count == 0;
}

template<typename T>
bool Queue<T>::is_full() const noexcept {
    return _count == _size;
}

template<typename T>
void Queue<T>::clear() noexcept {
    _front = 0;
    _count = 0;
}

#endif  // LIBS_LIB_QUEUE_QUEUE_H_
