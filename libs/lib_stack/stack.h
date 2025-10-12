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
    bool is_empty();
    bool is_full();
    void clear();
};

template<typename T>
Stack<T>::Stack(size_t size) : _data(new T[size]), _top(-1), _size(size) {}

template<typename T>
Stack<T>::Stack(const Stack& other) : _top(other._top), _size(other._size) {
    _data = new T[_size];

    for (size_t i = 0; i < _size; i++)
        _data[i] = other._data[i];
}

template<typename T>
Stack<T>::~Stack() {
    delete[] _data;
}

template<typename T>
void Stack<T>::push(const T& value) {
}

template<typename T>
void Stack<T>::pop() {
}

template<typename T>
T& Stack<T>::top() {
    return _data[0];
}

template<typename T>
bool Stack<T>::is_empty() {
    return false;
}

template<typename T>
bool Stack<T>::is_full() {
    return false;
}

template<typename T>
void Stack<T>::clear() {
}

#endif  // LIBS_LIB_STACK_STACK_H_
