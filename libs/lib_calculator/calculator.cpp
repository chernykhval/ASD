// Copyright 2025 Chernykh Valentin


#include <string>
#include <sstream>
#include "libs/lib_calculator/calculator.h"
#include "libs/lib_math/math.h"

Calculator::Calculator() {
    _vars.add("pi", 3.1415926535);
    _vars.add("e", 2.7182818284);

    _functions.add("sin", Math::sin);
    _functions.add("cos", Math::cos);
    _functions.add("tg", Math::tg);
    _functions.add("ln", Math::ln);
    _functions.add("sqrt", Math::sqrt);
}

Calculator::Calculator(const VarTable& vars, const FunctionTable& functions) :
_vars(vars), _functions(functions) {
}

Calculator::Calculator(const Calculator& other) :
_vars(other._vars), _functions(other._functions) {
}

void Calculator::add_variable(const std::string& name, double value) {
    _vars.add(name, value);
}

void Calculator::remove_variable(const std::string& name) {
    _vars.remove(name);
}

void Calculator::add_expression(const std::string& input) {
    _expressions.push_back(Expression(input, _vars, _functions));
}

void Calculator::remove_expression(size_t index) {
    if (index >= _expressions.size()) {
        throw std::out_of_range("Index to delete out of range");
    }

    _expressions.erase(_expressions.begin() + index);
}

double Calculator::calculate(size_t index) const {
    if (index >= _expressions.size()) {
        throw std::out_of_range("Expression index out of range");
    }

    return _expressions[index].calculate(_vars, _functions);
}

std::string Calculator::info() const {
    std::stringstream ss;

    ss << vars_info() << "\n" << functions_info() << "\n" << expressions_info();

    return ss.str();
}

std::string Calculator::vars_info() const {
    std::stringstream ss;

    ss << "=== VARIABLES ===\n";
    ss << _vars.info();

    return ss.str();
}

std::string Calculator::functions_info() const {
    std::stringstream ss;

    ss << "=== FUNCTIONS ===\n";
    ss << _functions.info();

    return ss.str();
}

std::string Calculator::expressions_info() const {
    std::stringstream ss;

    ss << "=== EXPRESSIONS ===\n";

    if (_expressions.is_empty()) {
        ss << "No expressions added.\n";
        return ss.str();
    }

    for (size_t i = 0; i < _expressions.size(); i++) {
        ss << i + 1 << ". " << _expressions[i].to_infix_string() << "\n";
    }

    return ss.str();
}
