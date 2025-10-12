// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_STACK_STACK_H_
#define LIBS_LIB_STACK_STACK_H_

#include <cstddef>
#include <stdexcept>

template<typename T>
class Stack {
 private:
    T* _data;
    size_t _top;
    size_t _size;

 public:
    explicit Stack(size_t size);
    Stack(const Stack& other);
    ~Stack() noexcept;

    void push(const T& value);
    void pop();
    T& top();
    bool is_empty() const noexcept;
    bool is_full() const noexcept;
    void clear() noexcept;
};

template<typename T>
Stack<T>::Stack(size_t size) {
    if (size == 0) {
        throw std::invalid_argument("Stack size cannot be 0");
    }

    _data = new T[size];
    _top = -1;
    _size = size;
}

template<typename T>
Stack<T>::Stack(const Stack& other) : _top(other._top), _size(other._size) {
    _data = new T[_size];

    for (size_t i = 0; i <= _top; i++)
        _data[i] = other._data[i];
}

template<typename T>
Stack<T>::~Stack() noexcept {
    delete[] _data;
}

template<typename T>
void Stack<T>::push(const T& value) {
    if (is_full()) {
        throw std::overflow_error("Stack is full");
    }

    _data[++_top] = value;
}

template<typename T>
void Stack<T>::pop() {
    if (is_empty()) {
        throw std::underflow_error("Stack is empty");
    }

    --_top;
}

template<typename T>
T& Stack<T>::top() {
    if (is_empty()) {
        throw std::underflow_error("Stack is empty");
    }

    return _data[_top];
}

template<typename T>
bool Stack<T>::is_empty() const noexcept {
    return _top == -1;
}

template<typename T>
bool Stack<T>::is_full() const noexcept {
    return _top == _size - 1;
}

template<typename T>
void Stack<T>::clear() noexcept {
    _top = -1;
}

#endif  // LIBS_LIB_STACK_STACK_H_
