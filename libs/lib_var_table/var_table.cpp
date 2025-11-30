// Copyright 2025 Chernykh Valentin

#include <string>
#include <sstream>
#include "libs/lib_var_table/var_table.h"

Variable::Variable() : value(0.0) {
}

Variable::Variable(const std::string &_name, double _value)
: name(_name), value(_value) {
}

std::string Variable::info() const {
    std::stringstream ss;
    ss << name << " = " << value;

    return ss.str();
}

void VarTable::add(const std::string& name, double value) {
    int index = find_index(name);

    if (index != -1) {
        _vars[index].value = value;
    } else {
        _vars.push_back(Variable(name, value));
    }
}

void VarTable::remove(const std::string& name) {
    for (auto it = _vars.begin(); it != _vars.end(); ++it) {
        if (it->name == name) {
            _vars.erase(it);
            return;
        }
    }

    throw std::invalid_argument("Variable does not exist");
}

double VarTable::get(const std::string& name) const {
    int index = find_index(name);

    if (index != -1) {
        return _vars[index].value;
    }

    throw std::runtime_error("Variable not found: " + name);
}

bool VarTable::contains(const std::string& name) const {
    return find_index(name) != -1;
}

std::string VarTable::info() const {
    std::stringstream ss;

    if (_vars.is_empty()) {
        return "No variables set";
    }

    for (const auto& var : _vars) {
        ss << var.info() << "\n";
    }

    return ss.str();
}

int VarTable::find_index(const std::string& name) const {
    for (size_t i = 0; i < _vars.size(); ++i) {
        if (_vars[i].name == name) {
            return static_cast<int>(i);
        }
    }

    return -1;
}
