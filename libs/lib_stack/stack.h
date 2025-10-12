// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_STACK_STACK_H_
#define LIBS_LIB_STACK_STACK_H_

#include <cstddef>

template<typename T>
class Stack {
 private:
    T* _data;
    size_t _top;
    size_t _size;

 public:
    explicit Stack(size_t size);
    Stack(const Stack& other);
    ~Stack();

    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;
    T copy_top();
    bool is_empty();
    bool is_full();
    void clear();
};

#endif  // LIBS_LIB_STACK_STACK_H_
