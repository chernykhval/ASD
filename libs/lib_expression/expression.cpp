// Copyright 2025 Chernykh Valentin

#include <string>
#include "libs/lib_expression/expression.h"

Expression::Expression(const std::string& expression) :
_expression(expression) {
}

void Expression::init_lexemes() {
    for (char c : _expression) {
    }
}
