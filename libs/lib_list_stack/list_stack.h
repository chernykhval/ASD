// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_LIST_STACK_LIST_STACK_H_
#define LIBS_LIB_LIST_STACK_LIST_STACK_H_

#include "libs/lib_list/list.h"

template<typename T>
class ListStack {
 private:
    List<T> _data;

 public:
    explicit ListStack();
    ListStack(const ListStack& other);

    void push(const T& value);
    void pop();
    T& top();
    bool is_empty() const noexcept;
    void clear() noexcept;
};

template<typename T>
ListStack<T>::ListStack() : _data() {
}

template<typename T>
ListStack<T>::ListStack(const ListStack& other) : _data(other._data) {
}

template<typename T>
void ListStack<T>::push(const T& value) {
    _data.push_front(value);
}

template<typename T>
void ListStack<T>::pop() {
    if (is_empty()) {
        throw std::underflow_error("Stack is empty");
    }

    _data.pop_front();
}

template<typename T>
T& ListStack<T>::top() {
    if (is_empty()) {
        throw std::underflow_error("Stack is empty");
    }

    return  *_data.begin();
}

template<typename T>
bool ListStack<T>::is_empty() const noexcept {
    return _data.is_empty();
}

template<typename T>
void ListStack<T>::clear() noexcept {
    _data.clear();
}


#endif  // LIBS_LIB_LIST_STACK_LIST_STACK_H_
