// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
#define LIBS_LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H_

#include <string>
#include <sstream>
#include "libs/lib_heap/heap.h"

template<typename T>
class PriorityQueue {
 private:
    struct PriorityPair {
        int priority;
        size_t seq;
        T value;

        PriorityPair() : priority(0), value(), seq(0) {
        }
        PriorityPair(int priority, T value, size_t seq) : priority(priority),
        value(value), seq(seq) {
        }

        bool operator<(const PriorityPair &p) const {
            if (priority == p.priority) {
                return seq < p.seq;
            }

            return priority < p.priority;
        }

        bool operator>(const PriorityPair &p) const {
            return p < *this;
        }
    };

    Heap<PriorityPair> _heap;
    size_t _counter;

 public:
    PriorityQueue() noexcept;

    void push(int priority, T value);
    T pop();
    T top() const;
    int top_priority() const;
    bool is_empty() const noexcept;
};

template<typename T>
PriorityQueue<T>::PriorityQueue() noexcept : _heap(), _counter(0) {
}

template<typename T>
void PriorityQueue<T>::push(int priority, T value) {
    PriorityPair p(priority, value, _counter);
    _counter++;
    _heap.insert(p);
}

template<typename T>
T PriorityQueue<T>::pop() {
    return _heap.pop().value;
}

template<typename T>
T PriorityQueue<T>::top() const {
    return _heap.top().value;
}

template<typename T>
int PriorityQueue<T>::top_priority() const {
    return _heap.top().priority;
}

template<typename T>
bool PriorityQueue<T>::is_empty() const noexcept {
    return _heap.is_empty();
}


#endif  // LIBS_LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
