// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_CALCULATOR_APP_CALCULATOR_APP_H_
#define LIBS_LIB_CALCULATOR_APP_CALCULATOR_APP_H_

#include "libs/lib_calculator/calculator.h"
#include "libs/lib_calculator_app/calculator_app.h"

enum class Command {
    Exit = 0,
    Info,
    AddVariable,
    RemoveVariable,
    AddExpression,
    RemoveExpression,
    CalculateExpression
};

class CalculatorApp {
 private:
    Calculator& _calculator;

 public:
    explicit CalculatorApp(Calculator& calculator);

    void run();

private:
    void print_menu();
    void print_info();
    void add_variable();
    void remove_variable();
    void add_expression();
    void remove_expression();
    void calculate_expression();
    void wait_for_enter();
    void clear_screen();

};

#endif  // LIBS_LIB_CALCULATOR_APP_CALCULATOR_APP_H_