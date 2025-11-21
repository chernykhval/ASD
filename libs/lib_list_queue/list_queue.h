// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_LIST_QUEUE_LIST_QUEUE_H_
#define LIBS_LIB_LIST_QUEUE_LIST_QUEUE_H_

#include "libs/lib_list/list.h"

template<typename T>
class ListQueue {
 private:
    List<T> _data;

 public:
    explicit ListQueue();
    ListQueue(const ListQueue& other);

    void enqueue(const T& value);
    void dequeue();
    T& front();
    bool is_empty() const noexcept;
    void clear() noexcept;
};

template<typename T>
ListQueue<T>::ListQueue() : _data() {
}

template<typename T>
ListQueue<T>::ListQueue(const ListQueue& other) : _data(other) {
}

template<typename T>
void ListQueue<T>::enqueue(const T& value) {
    _data.push_back(value);
}

template<typename T>
void ListQueue<T>::dequeue() {
    if (is_empty()) {
        throw std::underflow_error("Queue is empty");
    }

    _data.pop_front();
}

template<typename T>
T & ListQueue<T>::front() {
    if (is_empty()) {
        throw std::underflow_error("Queue is empty");
    }

    return *_data.begin();
}

template<typename T>
bool ListQueue<T>::is_empty() const noexcept {
    return _data.is_empty();
}

template<typename T>
void ListQueue<T>::clear() noexcept {
    _data.clear();
}


#endif  // LIBS_LIB_LIST_QUEUE_LIST_QUEUE_H_
