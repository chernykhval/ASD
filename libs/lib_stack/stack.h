// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_STACK_STACK_H_
#define LIBS_LIB_STACK_STACK_H_

#include "libs/lib_tvector/tvector.h"

template<typename T>
class Stack {
 private:
    TVector<T> _data;
    size_t _top;

public:
    explicit Stack(size_t size);
    Stack(const Stack& other);
    Stack(Stack&& other);

    void push(const T& value);
    void push(T&& value);
    void pop();
    T& top();
    const T& top() const;
    T copy_top();
    bool is_empty();
    bool is_full();
    void clear();
};

template<typename T>
Stack<T>::Stack(size_t size) : _data(), _top(-1) {
    _data.reserve(size);
};

#endif  // LIBS_LIB_STACK_STACK_H_
