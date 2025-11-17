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

        explicit Node(const T&, Node* next = nullptr,
            Node* prev = nullptr) noexcept;
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

    LinkedList() noexcept;
    LinkedList(const LinkedList&);
    ~LinkedList() noexcept;

    bool is_empty() const noexcept;

    void push_back(const T&);
    void push_front(const T&);
    void insert(size_t, const T&);
    void insert(const Iterator&, const T&);

    void pop_back();
    void pop_front();
    void erase(size_t);
    void erase(const Iterator&);

    void clear() noexcept;

    LinkedList& operator=(const LinkedList<T>&);

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
};

template<typename T>
LinkedList<T>::Node::Node(const T& value, Node* next, Node* prev) noexcept :
_value(value), _next(next), _prev(prev) {
}

template<typename T>
LinkedList<T>::Iterator::Iterator(Node* node) noexcept : _current(node) {
}

template<typename T>
LinkedList<T>::Iterator::Iterator(const Iterator& other) noexcept :
_current(other._current) {
}

template<typename T>
typename LinkedList<T>::Iterator::reference LinkedList<T>::Iterator::operator*() const {
    if (_current == nullptr) {
        throw std::runtime_error("List::Iterator::operator*"
            " - Dereferencing null iterator");
    }

    return _current->_value;
}

template<typename T>
typename LinkedList<T>::Iterator::pointer LinkedList<T>::Iterator::operator->() const {
    if (_current == nullptr) {
        throw std::runtime_error("List::Iterator::operator->"
            " - Dereferencing null iterator");
    }

    return &(_current->_value);
}

template<typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() {
    if (_current == nullptr) {
        throw std::runtime_error("List::Iterator::operator++"
                                 " - Cannot increment null iterator");
    }

    _current = _current->_next;

    return *this;
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int) {
    if (_current == nullptr) {
        throw std::runtime_error("List::Iterator::operator++(int)"
                                 " - Cannot increment null iterator");
    }

    Iterator temp = *this;
    _current = _current->_next;

    return temp;
}

template<typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator--() {
    if (_current == nullptr) {
        throw std::runtime_error("List::Iterator::operator--"
                                 " - Cannot decrement null iterator");
    }

    _current = _current->_prev;

    return *this;
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator--(int) {
    if (_current == nullptr) {
        throw std::runtime_error("List::Iterator::operator--(int)"
                                 " - Cannot decrement null iterator");
    }

    Iterator temp = *this;
    _current = _current->_prev;

    return temp;
}

template<typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& other) const noexcept {
    return _current != other._current;
}

template<typename T>
bool LinkedList<T>::Iterator::operator==(const Iterator& other) const noexcept {
    return _current == other._current;
}

template<typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator=(const Iterator& other)
noexcept {
    if (this != &other) {
        _current = other._current;
    }

    return *this;
}

template<typename T>
LinkedList<T>::ConstIterator::ConstIterator(const Node* node) noexcept :
_current(node) {
}

template<typename T>
LinkedList<T>::ConstIterator::ConstIterator(const ConstIterator& other) noexcept :
_current(other._current) {
}

template<typename T>
typename LinkedList<T>::ConstIterator::reference LinkedList<T>::ConstIterator::operator*()
const {
    if (_current == nullptr) {
        throw std::runtime_error("List::ConstIterator::operator*"
                                 " - Dereferencing null iterator");
    }

    return _current->_value;
}

template<typename T>
typename LinkedList<T>::ConstIterator::pointer LinkedList<T>::ConstIterator::operator->()
const {
    if (_current == nullptr) {
        throw std::runtime_error("List::ConstIterator::operator->"
                                 " - Dereferencing null iterator");
    }

    return &(_current->_value);
}

template<typename T>
typename LinkedList<T>::ConstIterator& LinkedList<T>::ConstIterator::operator++() {
    if (_current == nullptr) {
        throw std::runtime_error("List::ConstIterator::operator++"
                                 " - Cannot increment null iterator");
    }

    _current = _current->_next;

    return *this;
}

template<typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::ConstIterator::operator++(int) {
    if (_current == nullptr) {
        throw std::runtime_error("List::ConstIterator::operator++(int)"
                                 " - Cannot increment null iterator");
    }

    ConstIterator temp = *this;
    _current = _current->_next;

    return temp;
}

template<typename T>
typename LinkedList<T>::ConstIterator& LinkedList<T>::ConstIterator::operator--() {
    if (_current == nullptr) {
        throw std::runtime_error("List::ConstIterator::operator--"
                                 " - Cannot decrement null iterator");
    }

    _current = _current->_prev;

    return *this;
}

template<typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::ConstIterator::operator--(int) {
    if (_current == nullptr) {
        throw std::runtime_error("List::ConstIterator::operator--(int)"
                                 " - Cannot decrement null iterator");
    }

    ConstIterator temp = *this;
    _current = _current->_prev;

    return temp;
}

template<typename T>
bool LinkedList<T>::ConstIterator::operator!=(const ConstIterator& other)
const noexcept {
    return _current != other._current;
}

template<typename T>
bool LinkedList<T>::ConstIterator::operator==(const ConstIterator& other)
const noexcept {
    return _current == other._current;
}

template<typename T>
typename LinkedList<T>::ConstIterator& LinkedList<T>::ConstIterator::
operator=(const ConstIterator& other) noexcept {
    if (this != &other) {
        _current = other._current;
    }

    return *this;
}

template<typename T>
LinkedList<T>::LinkedList() noexcept : _head(nullptr), _tail(nullptr), _size(0) {
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : _head(nullptr), _tail(nullptr), _size(0) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        push_back(*it);
    }
}

template<typename T>
LinkedList<T>::~LinkedList() noexcept {
    while (_head != nullptr) {
        Node* temp = _head;
        _head = _head->_next;
        delete temp;
    }
}

template<typename T>
bool LinkedList<T>::is_empty() const noexcept {
    return _head == nullptr;
}

template<typename T>
void LinkedList<T>::push_back(const T& value) {
    Node* node = new Node(value);

    if (is_empty()) {
        _head = node;
        _tail = node;
    } else {
        _tail->_next = node;
        node->_prev = _tail;
        _tail = node;
    }

    ++_size;
}

template<typename T>
void LinkedList<T>::push_front(const T& value) {
    Node* node = new Node(value);

    if (is_empty()) {
        _head = node;
        _tail = node;
    } else {
        node->_next = _head;
        _head->_prev = node;
        _head = node;
    }

    ++_size;
}

template<typename T>
void LinkedList<T>::insert(size_t pos, const T& value) {
    if (pos == 0) {
        push_front(value);
        return;
    }

    if (pos == _size) {
        push_back(value);
        return;
    }

    if (pos > _size) {
        throw std::out_of_range("List::insert pos out of size");
    }

    if (_head == nullptr) {
        throw std::runtime_error("List::insert - empty list");
    }

    if (pos - 1 <= _size - pos) {
        Node* current = _head;
        size_t current_pos = 0;

        while (current != nullptr) {
            if (current_pos == pos - 1) {
                break;
            }

            current = current->_next;
            ++current_pos;
        }

        insert(Iterator(current), value);
    } else {
        Node* current = _tail;
        size_t current_pos = _size - 1;

        while (current != nullptr) {
            if (current_pos == pos - 1) {
                break;
            }

            current = current->_prev;
            --current_pos;
        }

        insert(Iterator(current), value);
    }
}

template<typename T>
void LinkedList<T>::insert(const Iterator& iterator, const T& value) {
    if (iterator._current == nullptr || is_empty()) {
        throw std::runtime_error("List::insert - null iterator or empty list");
    }

    Node* new_node = new Node(value);

    new_node->_next = iterator._current->_next;
    new_node->_prev = iterator._current;
    new_node->_prev->_next = new_node;

    if (iterator._current == _tail) {
        _tail = new_node;
    } else {
        new_node->_next->_prev = new_node;
    }

    ++_size;
}

template<typename T>
void LinkedList<T>::pop_back() {
    if (is_empty()) {
        throw std::runtime_error("List::pop_back - empty list");
    }

    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
        return;
    }

    Node* node = _tail->_prev;
    delete _tail;
    _tail = node;
    _tail->_next = nullptr;
    --_size;
}

template<typename T>
void LinkedList<T>::pop_front() {
    if (is_empty()) {
        throw std::runtime_error("List::pop_front - empty list");
    }

    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
        return;
    }

    Node* node = _head->_next;
    delete _head;
    _head = node;
    _head->_prev = nullptr;
    --_size;
}

template<typename T>
void LinkedList<T>::erase(size_t pos) {
    if (pos == 0) {
        pop_front();
        return;
    }

    if (pos == _size - 1) {
        pop_back();
        return;
    }

    if (pos >= _size) {
        throw std::out_of_range("List::erase pos out of size");
    }

    if (_head == nullptr) {
        throw std::runtime_error("List::erase - empty list");
    }

    if (pos <= _size - pos - 1) {
        Node* current = _head;
        size_t current_pos = 0;

        while (current != nullptr) {
            if (current_pos == pos) {
                break;
            }

            current = current->_next;
            ++current_pos;
        }

        erase(Iterator(current));
    } else {
        Node* current = _tail;
        size_t current_pos = _size - 1;

        while (current != nullptr) {
            if (current_pos == pos) {
                break;
            }

            current = current->_prev;
            --current_pos;
        }

        erase(Iterator(current));
    }
}

template<typename T>
void LinkedList<T>::erase(const Iterator& iterator) {
    if (iterator._current == nullptr || is_empty()) {
        throw std::runtime_error("List::erase - null iterator or empty list");
    }

    if (iterator._current == _head) {
        pop_front();
        return;
    }

    if (iterator._current == _tail) {
        pop_back();
        return;
    }

    Node* prev = iterator._current->_prev;

    prev->_next = iterator._current->_next;
    iterator._current->_next->_prev = prev;
    delete iterator._current;
    --_size;
}

template<typename T>
void LinkedList<T>::clear() noexcept {
    while (_head != nullptr) {
        Node* temp = _head;
        _head = _head->_next;
        delete temp;
    }

    _tail = nullptr;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {
        clear();

        for (auto it = other.begin(); it != other.end(); ++it) {
            push_back(*it);
        }
    }

    return *this;
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() noexcept {
    return Iterator(_head);
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() noexcept {
    return Iterator(nullptr);
}

template<typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::begin() const noexcept {
    return ConstIterator(_head);
}

template<typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::end() const noexcept {
    return ConstIterator(nullptr);
}

#endif  // LIBS_LIB_LINKED_LIST_LINKED_LIST_H_
