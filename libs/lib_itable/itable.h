// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_ITABLE_ITABLE_H_
#define LIBS_LIB_ITABLE_ITABLE_H_

#include <string>
#include "libs/lib_tvector/tvector.h"

template <typename Key, typename Value>
class ITable {
 public:
    virtual ~ITable() = default;
    virtual void insert(const Key& key, const Value& value) = 0;
    virtual void erase(const Key& key) = 0;
    virtual Value* find(const Key& key) = 0;
    virtual const Value* find(const Key& key) const = 0;
    virtual bool is_empty() const = 0;
    virtual void clear() = 0;
    virtual size_t size() const = 0;
    virtual std::string to_string() const = 0;
    virtual TVector<Key> get_keys() const = 0;
    virtual bool contains(const Key& key) const = 0;
};

#endif  // LIBS_LIB_ITABLE_ITABLE_H_
