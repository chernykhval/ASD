// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_LINKED_LIST_LINKED_LIST_H_
#define LIBS_LIB_LINKED_LIST_LINKED_LIST_H_

#include <cstddef>
#include <stdexcept>

template<typename T>
class LinkedList {
 private:
    struct Node {
        T _value;
        Node* _next;
        Node* _prev;

        explicit Node(const T&, Node* next = nullptr) noexcept;
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
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = LinkedList::value_type;
        using reference = LinkedList::reference;
        using pointer = LinkedList::pointer;
        using difference_type = LinkedList::difference_type;

        explicit Iterator(Node* node) noexcept;
        Iterator(const Iterator&) noexcept;

        reference operator*() const;
        pointer operator->() const;

        Iterator& operator++();
        Iterator operator++(int);

        Iterator& operator--();
        Iterator operator--(int);

        bool operator!=(const Iterator&) const noexcept;
        bool operator==(const Iterator&) const noexcept;

        Iterator& operator=(const Iterator&) noexcept;

        friend class LinkedList<T>;
    };

    class ConstIterator {
    private:
        const Node* _current;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = LinkedList::value_type;
        using reference = LinkedList::const_reference;
        using pointer = LinkedList::const_pointer;
        using difference_type = LinkedList::difference_type;

        explicit ConstIterator(const Node*) noexcept;
        ConstIterator(const ConstIterator&) noexcept;

        reference operator*() const;
        pointer operator->() const;

        ConstIterator& operator++();
        ConstIterator operator++(int);

        ConstIterator& operator--();
        ConstIterator operator--(int);

        bool operator!=(const ConstIterator&) const noexcept;
        bool operator==(const ConstIterator&) const noexcept;

        ConstIterator& operator=(const ConstIterator&) noexcept;
    };

    LinkedList();
    LinkedList(const LinkedList&);
    ~LinkedList();

    bool is_empty();

    void push_back(const T&);
    void push_front(const T&);
    void insert(size_t, const T&);
    void insert(const Iterator&, const T&);

    void pop_back();
    void pop_front();
    void erase(size_t);
    void erase(const Iterator&);

    void clear();

    LinkedList& operator=(const LinkedList<T>&);

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
};

#endif  // LIBS_LIB_LINKED_LIST_LINKED_LIST_H_
