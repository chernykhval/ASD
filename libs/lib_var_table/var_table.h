// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_VAR_TABLE_VAR_TABLE_H_
#define LIBS_LIB_VAR_TABLE_VAR_TABLE_H_

#include <string>
#include "libs/lib_tvector/tvector.h"

struct Variable {
    std::string name;
    double value;

    Variable();
    Variable(const std::string& _name, double _value);
};

class VarTable {
 private:
    TVector<Variable> _vars;

 public:
    void add(const std::string& name, double value);
    double get(const std::string& name) const;
    bool contains(const std::string& name) const;

 private:
    int find_index(const std::string& name) const;
};

#endif  // LIBS_LIB_VAR_TABLE_VAR_TABLE_H_
