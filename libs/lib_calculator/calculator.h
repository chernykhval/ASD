// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_CALCULATOR_CALCULATOR_H_
#define LIBS_LIB_CALCULATOR_CALCULATOR_H_

#include <string>
#include "libs/lib_expression/expression.h"
#include "libs/lib_var_table/var_table.h"
#include "libs/lib_function_table/function_table.h"
#include "libs/lib_tvector/tvector.h"

class Calculator {
 private:
    VarTable _vars;
    FunctionTable _functions;
    TVector<Expression> _expressions;

 public:
    Calculator();
    Calculator(const VarTable& vars, const FunctionTable& functions);
    Calculator(const Calculator& other);

    void add_variable(const std::string& name, double value);
    void remove_variable(const std::string& name);
    void add_expression(const std::string& input);
    void remove_expression(size_t index);
    double calculate(size_t index) const;
    std::string info() const;
    std::string vars_info() const;
    std::string functions_info() const;
    std::string expressions_info() const;
};

#endif  // LIBS_LIB_CALCULATOR_CALCULATOR_H_
