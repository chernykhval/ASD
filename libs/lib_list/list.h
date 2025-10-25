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

       explicit Node(const T&);
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

        explicit Iterator(Node*);
        Iterator(const Iterator&);

        reference operator*();
        pointer operator->();

        Iterator& operator++();
        Iterator operator++(int);

        bool operator!=(const Iterator&);
        bool operator==(const Iterator&);

        Iterator& operator=(const Iterator&);
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

        explicit ConstIterator(const Node*);
        ConstIterator(const ConstIterator&);

        reference operator*();
        pointer operator->();

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
List<T>::Node::Node(const T& value) : _value(value), _next(nullptr) {}

#endif  // LIBS_LIB_LIST_LIST_H_
