// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_HEAP_HEAP_H_
#define LIBS_LIB_HEAP_HEAP_H_

#include <string>
#include <sstream>

#include "libs/lib_tvector/tvector.h"

template <typename T>
class Heap {
 private:
    TVector<T> vec;

 public:
    Heap();
    void insert(const T&);
    T pop();
    bool is_empty() const;
    void clear();
    const T& top() const;
    size_t size() const;

 private:
    void surface(size_t index);
    void dive();
};

template<typename T>
Heap<T>::Heap() : vec() {
}

template<typename T>
void Heap<T>::insert(const T& value) {
    vec.push_back(value);
    surface(vec.size() - 1);
}

template<typename T>
T Heap<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("Heap::top: heap is empty");
    }

    T value = vec[0];

    vec[0] = vec[vec.size() - 1];
    vec.pop_back();
    dive();

    return value;
}

template<typename T>
bool Heap<T>::is_empty() const {
    return vec.is_empty();
}

template<typename T>
void Heap<T>::clear() {
    vec.clear();
}

template<typename T>
const T& Heap<T>::top() const {
    if (is_empty()) {
        throw std::logic_error("Heap::top: heap is empty");
    }

    return vec[0];
}

template<typename T>
size_t Heap<T>::size() const {
    return vec.size();
}

template<typename T>
void Heap<T>::surface(size_t index) {
    int parent_index;

    while (index > 0) {
        if (index % 2 == 1) {
            parent_index = (index - 1) / 2;
        } else {
            parent_index = (index - 2) / 2;
        }

        if (vec[parent_index] > vec[index]) {
            T tmp = vec[index];
            vec[index] = vec[parent_index];
            vec[parent_index] = tmp;
        } else {
            break;
        }

        index = parent_index;
    }
}

template<typename T>
void Heap<T>::dive() {
    int current = 0;
    int left, right, swap_index, vec_size = vec.size();

    while (true) {
        left = current * 2 + 1;
        right = current * 2 + 2;
        swap_index = -1;

        if (right < vec_size && vec[right] < vec[current]) {
            swap_index = right;
        }

        if (left < vec_size && vec[left] < vec[current]) {
            if (swap_index == -1 || (right < vec_size && vec[right] > vec[left])) {
                swap_index = left;
            }
        }

        if (swap_index == -1) {
            break;
        }

        T tmp = vec[current];
        vec[current] = vec[swap_index];
        vec[swap_index] = tmp;
        current = swap_index;
    }
}

#endif  // LIBS_LIB_HEAP_HEAP_H_
