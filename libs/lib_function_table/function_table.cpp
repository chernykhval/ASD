// Copyright 2025 Chernykh Valentin

#include <string>
#include "libs/lib_function_table/function_table.h"

void FunctionTable::add(const std::string& name, UnaryFunc func_ptr) {
    if (contains(name)) {
        throw std::runtime_error("Function already exists: " + name);
    }
    _functions.push_back({name, func_ptr});
}

UnaryFunc FunctionTable::get(const std::string& name) const {
    int index = find_index(name);

    if (index != -1) {
        return _functions[index].funcPtr;
    }

    throw std::runtime_error("Function not found: " + name);
}

bool FunctionTable::contains(const std::string& name) const {
    return find_index(name) != -1;
}

int FunctionTable::find_index(const std::string& name) const {
    for (size_t i = 0; i < _functions.size(); ++i) {
        if (_functions[i].name == name) {
            return static_cast<int>(i);
        }
    }

    return -1;
}
