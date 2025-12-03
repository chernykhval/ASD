// Copyright 2025 Chernykh Valentin

#include <string>
#include <sstream>
#include "libs/lib_function_table/function_table.h"

Function::Function(const std::string& _name, UnaryFunc _func_ptr) :
name(_name), func_ptr(_func_ptr) {
}

std::string Function::info() const {
    std::stringstream ss;
    ss << name << "(var)";

    return ss.str();
}

void FunctionTable::add(const std::string& name, UnaryFunc func_ptr) {
    if (contains(name)) {
        throw std::runtime_error("Function already exists: " + name);
    }
    _functions.push_back({name, func_ptr});
}

UnaryFunc FunctionTable::get(const std::string& name) const {
    int index = find_index(name);

    if (index != -1) {
        return _functions[index].func_ptr;
    }

    throw std::runtime_error("Function not found: " + name);
}

bool FunctionTable::contains(const std::string& name) const {
    return find_index(name) != -1;
}

std::string FunctionTable::info() const {
    std::stringstream ss;

    if (_functions.is_empty()) {
        return "No functions set";
    }

    for (const auto& func : _functions) {
        ss << func.info() << "\n";
    }

    return ss.str();
}

int FunctionTable::find_index(const std::string& name) const {
    for (size_t i = 0; i < _functions.size(); ++i) {
        if (_functions[i].name == name) {
            return static_cast<int>(i);
        }
    }

    return -1;
}
