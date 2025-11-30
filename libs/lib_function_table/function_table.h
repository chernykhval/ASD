// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_FUNCTION_TABLE_FUNCTION_TABLE_H_
#define LIBS_LIB_FUNCTION_TABLE_FUNCTION_TABLE_H_

#include <string>
#include "libs/lib_tvector/tvector.h"

using UnaryFunc = double(*)(double);

struct Function {
    std::string name;
    UnaryFunc func_ptr;

    Function() = default;
    Function(const std::string& _name, UnaryFunc _func_ptr);
    Function(const Function& other) = default;

    std::string info() const;
};

class FunctionTable {
 private:
    TVector<Function> _functions;

 public:
    FunctionTable() = default;
    FunctionTable(const FunctionTable& other) = default;

    void add(const std::string& name, UnaryFunc func_ptr);
    UnaryFunc get(const std::string& name) const;
    bool contains(const std::string& name) const;

    std::string info() const;

 private:
    int find_index(const std::string& name) const;
};

#endif  // LIBS_LIB_FUNCTION_TABLE_FUNCTION_TABLE_H_
