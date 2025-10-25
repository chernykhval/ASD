// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_LIST_LIST_H_
#define LIBS_LIB_LIST_LIST_H_

#include <cstddef>
#include <stdexcept>

template<typename T>
class List {
 private:
    struct Node {
        T _value;
        Node* _next;

       explicit Node(const T&) noexcept;
    };

    Node *_head, *_tail;
    size_t _size;

 public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    class Iterator {
     private:
        Node* _current;

     public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = List::value_type;
        using reference = List::reference;
        using pointer = List::pointer;
        using difference_type = List::difference_type;

        explicit Iterator(Node*) noexcept;
        Iterator(const Iterator&) noexcept;

        reference operator*() const;
        pointer operator->() const;

        Iterator& operator++();
        Iterator operator++(int);

        bool operator!=(const Iterator&) const noexcept;
        bool operator==(const Iterator&) const noexcept;

        Iterator& operator=(const Iterator&) noexcept;
    };

    class ConstIterator {
     private:
        const Node* _current;

     public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = List::value_type;
        using reference = List::const_reference;
        using pointer = List::const_pointer;
        using difference_type = List::difference_type;

        explicit ConstIterator(const Node*) noexcept;
        ConstIterator(const ConstIterator&) noexcept;

        reference operator*() const;
        pointer operator->() const;

        ConstIterator& operator++();
        ConstIterator operator++(int);

        bool operator!=(const ConstIterator&);
        bool operator==(const ConstIterator&);

        ConstIterator& operator=(const ConstIterator&);
    };

    List();
    List(const List&);
    ~List();

    bool is_empty();
    void push_back(const T&);
    void push_front(const T&);
    void insert(size_t, const T&);
    void insert(Node*, const T&);
    void insert(const Iterator&, const T&);

    void pop_back();
    void pop_front();
    void erase(size_t);
    void erase(Node*);
    void erase(const Iterator&);

    void clear();

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
};

template<typename T>
List<T>::Node::Node(const T& value) noexcept : _value(value), _next(nullptr) {}

template<typename T>
List<T>::Iterator::Iterator(Node* node) noexcept : _current(node) {}

template<typename T>
List<T>::Iterator::Iterator(const Iterator& other) noexcept : _current(other._current) {}

template<typename T>
typename List<T>::Iterator::reference List<T>::Iterator::operator*() const {
   if (_current == nullptr) {
      throw std::runtime_error("List::Iterator::operator* - Dereferencing end iterator");
   }

   return _current->_value;
}

template<typename T>
typename List<T>::Iterator::pointer List<T>::Iterator::operator->() const {
   if (_current == nullptr) {
      throw std::runtime_error("List::Iterator::operator-> - Dereferencing end iterator");
   }

   return &(_current->_value);
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
   if (_current->_next == nullptr) {
      throw std::runtime_error("List::Iterator::operator++ - Cannot increment end iterator");
   }

   _current = _current->_next;

   return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
   if (_current == nullptr) {
      throw std::runtime_error("List::Iterator::operator++(int) - Cannot increment end iterator");
   }

   Iterator temp = *this;
   _current = _current->_next;

   return temp;
}

template<typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const noexcept {
   return _current != other._current;
}

template<typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const noexcept {
   return _current == other._current;
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator=(const Iterator& other) noexcept {
   if (this != &other) {
      _current = other._current;
   }

   return *this;
}

template<typename T>
List<T>::ConstIterator::ConstIterator(const Node* node) noexcept : _current(node) {}

template<typename T>
List<T>::ConstIterator::ConstIterator(const ConstIterator& other) noexcept : _current(other._current) {}

template<typename T>
typename List<T>::ConstIterator::reference List<T>::ConstIterator::operator*() const {
   if (_current == nullptr) {
      throw std::runtime_error("List::ConstIterator::operator* - Dereferencing end iterator");
   }

   return _current->_value;
}

template<typename T>
typename List<T>::ConstIterator::pointer List<T>::ConstIterator::operator->() const {
   if (_current == nullptr) {
      throw std::runtime_error("List::ConstIterator::operator-> - Dereferencing end iterator");
   }

   return &(_current->_value);
}

template<typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator++() {
   if (_current == nullptr) {
      throw std::runtime_error("List::ConstIterator::operator++ - Cannot increment end iterator");
   }

   _current = _current->_next;

   return *this;
}

template<typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int) {
   if (_current == nullptr) {
      throw std::runtime_error("List::ConstIterator::operator++(int) - Cannot increment end iterator");
   }

   ConstIterator temp = *this;
   _current = _current->_next;

   return temp;
}

#endif  // LIBS_LIB_LIST_LIST_H_
