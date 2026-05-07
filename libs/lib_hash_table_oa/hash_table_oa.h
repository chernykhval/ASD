// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_HASH_TABLE_OA_HASH_TABLE_OA_H_
#define LIBS_LIB_HASH_TABLE_OA_HASH_TABLE_OA_H_

#include <string>
#include <sstream>

#include "libs/lib_itable/itable.h"
#include "libs/lib_tvector/tvector.h"

#define ROWS_COUNT 100
#define SHIFT 7

template<typename Value>
class HashTableOA : public ITable<std::string, Value> {
 private:
    enum State {
        BUSY,
        EMPTY,
        DELETED
    };

    struct HashTableData {
        std::string key;
        Value value;
        State state;

        HashTableData() : key(), value(), state(EMPTY) {
        }
    };

    size_t _rows_count;
    size_t _busy_count;
    size_t _shift;
    HashTableData *_rows;

 public:
    explicit HashTableOA(size_t rows_count = ROWS_COUNT);
    ~HashTableOA();

    void insert(const std::string& key, const Value& value) override;
    bool erase(const std::string& key) override;
    Value* find(const std::string& key) noexcept override;
    const Value* find(const std::string& key) const noexcept override;
    bool is_empty() const noexcept override;
    void clear() noexcept override;
    size_t size() const noexcept override;
    std::string to_string() const override;
    TVector<std::string> get_keys() const override;
    bool contains(const std::string& key) const noexcept override;

private:
    size_t h(const std::string& key) const noexcept;
    size_t hh(size_t index) const noexcept;
    bool is_relatively_prime(size_t index_1, size_t index_2) const noexcept;
};

template<typename Value>
HashTableOA<Value>::HashTableOA(size_t rows_count) : _rows_count(rows_count), _busy_count(0), _shift(SHIFT) {
    _rows = new HashTableData[_rows_count];

    for (size_t i = _rows_count/15 + 1; i < _rows_count; i++) {
        if (is_relatively_prime(i, _rows_count)) {
            _shift = i;
            break;
        }
    }
}

template<typename Value>
HashTableOA<Value>::~HashTableOA() {
    delete[] _rows;
}

template<typename Value>
void HashTableOA<Value>::insert(const std::string& key, const Value& value) {
    if (_rows_count == _busy_count) {
        throw std::out_of_range("HashTableOA::insert: table is full");
    }

    size_t hash = h(key);
    size_t first_hash = hash;
    size_t first_deleted = _rows_count;

    while (true) {
        if (_rows[hash].state == EMPTY) {
            break;
        }

        if (_rows[hash].state == DELETED && first_deleted == _rows_count) {
            first_deleted = hash;
        } else if (_rows[hash].state == BUSY && _rows[hash].key == key) {
            throw std::invalid_argument("HashTableOA::insert: key already exists");
        }

        hash = hh(hash);

        if (hash == first_hash) {
            break;
        }
    }

    size_t insert_at = (first_deleted != _rows_count) ? first_deleted : hash;
    _rows[insert_at].key = key;
    _rows[insert_at].value = value;
    _rows[insert_at].state = BUSY;
    _busy_count++;
}

template<typename Value>
bool HashTableOA<Value>::erase(const std::string& key) {
    size_t hash = h(key);
    size_t first_hash = hash;

    while (true) {
        if (_rows[hash].state == EMPTY) {
            return false;
        }

        if (_rows[hash].state == BUSY && _rows[hash].key == key) {
            _rows[hash].state = DELETED;
            _busy_count--;
            return true;
        }

        hash = hh(hash);

        if (hash == first_hash) {
            return false;
        }
    }
}

template<typename Value>
Value* HashTableOA<Value>::find(const std::string& key) noexcept {
    size_t hash = h(key);
    size_t first_hash = hash;

    while (true) {
        if (_rows[hash].state == EMPTY) {
            return nullptr;
        }

        if (_rows[hash].state == BUSY && _rows[hash].key == key) {
            return &_rows[hash].value;
        }

        hash = hh(hash);

        if (hash == first_hash) {
            return nullptr;
        }
    }
}

template<typename Value>
const Value* HashTableOA<Value>::find(const std::string& key) const noexcept {
    size_t hash = h(key);
    size_t first_hash = hash;

    while (true) {
        if (_rows[hash].state == EMPTY) {
            return nullptr;
        }

        if (_rows[hash].state == BUSY && _rows[hash].key == key) {
            return &_rows[hash].value;
        }

        hash = hh(hash);

        if (hash == first_hash) {
            return nullptr;
        }
    }
}

template<typename Value>
bool HashTableOA<Value>::is_empty() const noexcept {
    return _busy_count == 0;
}

template<typename Value>
void HashTableOA<Value>::clear() noexcept {
    for (size_t i = 0; i < _rows_count; i++) {
        _rows[i].state = EMPTY;
    }

    _busy_count = 0;
}

template<typename Value>
size_t HashTableOA<Value>::size() const noexcept {
    return _busy_count;
}

template<typename Value>
std::string HashTableOA<Value>::to_string() const {
    std::stringstream ss;

    ss << "{key} : {value}\n";

    for (size_t i = 0; i < _rows_count; i++) {
        if (_rows[i].state == BUSY) {
            ss << "{" << _rows[i].key << "} : {" << _rows[i].value << "}\n";
        }
    }

    return ss.str();
}

template<typename Value>
TVector<std::string> HashTableOA<Value>::get_keys() const {
    TVector<std::string> keys;
    for (size_t i = 0; i < _rows_count; i++) {
        if (_rows[i].state == BUSY) {
            keys.push_back(_rows[i].key);
        }
    }
    return keys;
}

template<typename Value>
bool HashTableOA<Value>::contains(const std::string& key) const noexcept {
    return find(key) != nullptr;
}

template<typename Value>
size_t HashTableOA<Value>::h(const std::string& key) const noexcept {
    size_t hash = 0;

    for (auto l : key) {
        hash += l;
    }

    hash %= _rows_count;

    return hash;
}

template<typename Value>
size_t HashTableOA<Value>::hh(size_t index) const noexcept {
    return (index + _shift) % _rows_count;
}

template<typename Value>
bool HashTableOA<Value>::is_relatively_prime(size_t index_1, size_t index_2) const noexcept {
    size_t a, b, remainder = 0, last_reminder = 0;;
    a = index_1;
    b = index_2;

    while (true) {
        if (a < b) {
            size_t temp = a;
            a = b;
            b = temp;
        }

        last_reminder = remainder;
        remainder = a % b;

        if (remainder == 0) {
            break;
        }

        a = b;
        b = remainder;
    }

    return last_reminder == 1;
}

#endif  // LIBS_LIB_HASH_TABLE_OA_HASH_TABLE_OA_H_
