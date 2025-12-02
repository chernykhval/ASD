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
        _calculator.add_variable(name, value);
        std::cout << "Variable " << name << " = " << value << " added successfully." << std::endl;
    } else {
        throw std::runtime_error("Invalid number format for variable value");
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void CalculatorApp::remove_variable() {
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
    std::cin >> expression;

    try {
        _calculator.add_expression(expression);
    }
    catch (std::exception& e) {
        std::cout << "Variable " << expression << " addition failed." << std::endl;
        throw;
    }

    std::cout << "Expression " << expression << " added successfully.\nCheck info." << std::endl;
}

void CalculatorApp::remove_expression() {
    int expr_num;

    std::cout << "=== REMOVING EXPRESSION ===\n" << _calculator.expressions_info() << "Enter expression num: ";
    std::cin >> expr_num;

    try {
        _calculator.remove_expression(expr_num - 1);
    }
    catch (std::exception& e) {
        std::cout << "Expression number " << expr_num << " removing failed." << std::endl;
        throw std::out_of_range("Number to delete out of range");
    }

    std::cout << "Expression number " << expr_num << " remove successfully.\nCheck info." << std::endl;
}

void CalculatorApp::calculate_expression() {
    int expr_num;
    double result;

    std::cout << "=== CALCULATING EXPRESSION ===\n" << _calculator.expressions_info() << "Enter expression num: ";
    std::cin >> expr_num;

    try {
        result = _calculator.calculate(expr_num - 1);
    }
    catch (std::exception& e) {
        std::cout << "Expression number " << expr_num << " calculating failed." << std::endl;
        throw std::out_of_range("Number to delete out of range");
    }

    std::cout << "Expression number " << expr_num << " calculated successfully.\nExpression: "
    << "<to be developed>" <<"\nResult: " << result << std::endl;
}

void CalculatorApp::wait_for_enter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
    std::cin.get();
}

void CalculatorApp::clear_screen() {
    system("cls");
}
