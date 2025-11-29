// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_FUNCTION_TABLE_FUNCTION_TABLE_H_
#define LIBS_LIB_FUNCTION_TABLE_FUNCTION_TABLE_H_

#include <string>
#include "libs/lib_tvector/tvector.h"

using UnaryFunc = double(*)(double);

struct Function {
    std::string name;
    UnaryFunc funcPtr;
};

class FunctionTable {
 private:
    TVector<Function> _functions;

 public:
    void add(const std::string& name, UnaryFunc func_ptr);
    UnaryFunc get(const std::string& name);
    bool contains(const std::string& name);

 private:
    int find_index(const std::string& name);
};

#endif  // LIBS_LIB_FUNCTION_TABLE_FUNCTION_TABLE_H_
