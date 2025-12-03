// Copyright 2025 Chernykh Valentin

#include <string>
#include <limits>
#include "libs/lib_calculator_app/calculator_app.h"

CalculatorApp::CalculatorApp(Calculator& calculator) : _calculator(calculator) {
}

void CalculatorApp::run() {
    bool is_exit = false;

    while(!is_exit) {
        clear_screen();
        print_menu();

        int input;
        std::cout << "> ";

        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Command command = static_cast<Command>(input);

        try {
            switch (command) {
                case Command::Exit:
                    is_exit = true;
                    std::cout << "Exit Program..." << std::endl;
                    break;

                case Command::Info:
                    print_info();
                    break;

                case Command::AddVariable:
                    add_variable();
                    break;

                case Command::RemoveVariable:
                    remove_variable();
                    break;

                case Command::AddExpression:
                    add_expression();
                    break;

                case Command::RemoveExpression:
                    remove_expression();
                    break;

                case Command::CalculateExpression:
                    calculate_expression();
                    break;

                default:
                    std::cout << "Unknown command." << std::endl;
                    break;
            }
        }
        catch (const std::exception& e) {
            std::cout << "\n[ERROR]: " << e.what() << "\n" << std::endl;
        }

        wait_for_enter();
    }
}

void CalculatorApp::print_menu() {
    std::cout << "\n=== CALCULATOR MENU ===" << std::endl;
    std::cout << static_cast<int>(Command::Info) << ". Show Info" << std::endl;
    std::cout << static_cast<int>(Command::AddVariable) << ". Add Variable" << std::endl;
    std::cout << static_cast<int>(Command::RemoveVariable) << ". Remove Variable" << std::endl;
    std::cout << static_cast<int>(Command::AddExpression) << ". Add Expression" << std::endl;
    std::cout << static_cast<int>(Command::RemoveExpression) << ". Remove Expression" << std::endl;
    std::cout << static_cast<int>(Command::CalculateExpression) << ". Calculate Expression" << std::endl;
    std::cout << static_cast<int>(Command::Exit) << ". Exit" << std::endl;
    std::cout << "=======================" << std::endl;
}

void CalculatorApp::print_info() {
    std::cout << _calculator.info();
}

void CalculatorApp::add_variable() {
    std::string name;
    double value;

    std::cout << "=== ADDING VAR ===\nEnter name: ";
    std::cin >> name;
    std::cout << "Enter value: ";

    if (std::cin >> value) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        _calculator.add_variable(name, value);
        std::cout << "Variable " << name << " = " << value << " added successfully." << std::endl;
    } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Invalid number format for variable value");
    }
}

void CalculatorApp::remove_variable() {
    if (!_calculator.has_vars()) {
        std::cout << "List of variables is empty. Nothing to remove." << std::endl;
        return;
    }

    std::string name;

    std::cout <<  _calculator.vars_info() << "=== REMOVING VAR ===\n" << "Enter name: ";
    std::cin >> name;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    _calculator.remove_variable(name);
    std::cout << "Variable '" << name << "' removed successfully." << std::endl;
}

void CalculatorApp::add_expression() {
    std::string expression;

    std::cout << "=== ADDING EXPRESSION ===\nEnter expression: ";
    std::getline(std::cin, expression);

    if (expression.empty()) return;

    _calculator.add_expression(expression);
    std::cout << "Expression added successfully." << std::endl;
}

void CalculatorApp::remove_expression() {
    if (!_calculator.has_expressions()) {
        std::cout << "List of expressions is empty. Nothing to remove." << std::endl;
        return;
    }

    int expr_num;

    std::cout << _calculator.expressions_info() << "=== REMOVING EXPRESSION ===\n" << "Enter expression num: ";

    if (std::cin >> expr_num) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (expr_num < 1)
            throw std::out_of_range("Number must be >= 1");

        _calculator.remove_expression(expr_num - 1);
        std::cout << "Expression number " << expr_num << " removed successfully." << std::endl;
    } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Invalid number format");
    }
}

void CalculatorApp::calculate_expression() {
    int expr_num;

    std::cout << _calculator.expressions_info() << "=== CALCULATING EXPRESSION ===\n" << "Enter expression num: ";

    if (!(std::cin >> expr_num)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Invalid input");
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (expr_num < 1)
        throw std::out_of_range("Number must be >= 1");

    size_t index = expr_num - 1;
    double result = _calculator.calculate(index);

    std::cout << "Expression " << expr_num << " calculated successfully.\n";
    std::cout << "Formula: " << _calculator.get_substituted_expression(index) << "\n";
    std::cout << "Result: " << result << std::endl;
}

void CalculatorApp::wait_for_enter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void CalculatorApp::clear_screen() {
    system("cls");
}
