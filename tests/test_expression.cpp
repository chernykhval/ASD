// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include <cmath>
#include "libs/lib_expression/expression.h"
#include "libs/lib_var_table/var_table.h"
#include "libs/lib_function_table/function_table.h"

#define EPSILON 0.000001

class ExpressionTest : public ::testing::Test {
 protected:
    VarTable vars;
    FunctionTable funcs;

    void SetUp() override {
        vars.add("x", 10.0);
        vars.add("y", 20.0);
        vars.add("zero", 0.0);

        funcs.add("sin", std::sin);
        funcs.add("cos", std::cos);
        // funcs.add("my_func", [](double a) { return a; });
    }
};

TEST_F(ExpressionTest, SimpleAddition) {
    Expression expr("10 + 20", vars, funcs);

    ASSERT_EQ("RPN: [ 10 20 + ]", expr.to_postfix_string());
}

TEST_F(ExpressionTest, VariablesAndPriorities) {
    // x = 10, y = 20. Ожидаем: x + y * 2 -> x y 2 * +
    Expression expr("x + y * 2", vars, funcs);
    ASSERT_EQ("RPN: [ x y 2 * + ]", expr.to_postfix_string());
}

TEST_F(ExpressionTest, BracketsChangePriority) {
    // (x + y) * 2 -> x y + 2 *
    Expression expr("(x + y) * 2", vars, funcs);
    ASSERT_EQ("RPN: [ x y + 2 * ]", expr.to_postfix_string());
}

TEST_F(ExpressionTest, UnaryMinusAtStart) {
    // -x + 5 -> x u- 5 +
    Expression expr("-x + 5", vars, funcs);
    ASSERT_EQ("RPN: [ x u- 5 + ]", expr.to_postfix_string());
}

TEST_F(ExpressionTest, UnaryMinusInMiddle) {
    // 5 * -y -> 5 y u- *
    Expression expr("5 * -y", vars, funcs);
    ASSERT_EQ("RPN: [ 5 y u- * ]", expr.to_postfix_string());
}

TEST_F(ExpressionTest, Functions) {
    // sin(x) + 1 -> x sin 1 +
    Expression expr("sin(x) + 1", vars, funcs);
    ASSERT_EQ("RPN: [ x sin 1 + ]", expr.to_postfix_string());
}

// Если реализовал право-ассоциативность для степени или унарных минусов
TEST_F(ExpressionTest, RightAssociativity) {
    // - - x -> x u- u-
    Expression expr("- - x", vars, funcs);
    ASSERT_EQ("RPN: [ x u- u- ]", expr.to_postfix_string());
}

// === 3. Негативные тесты (Проверка Исключений) ===
// Мы проверяем, что код ПАДАЕТ с ошибкой, как и должен.

TEST_F(ExpressionTest, ThrowsOnUnknownIdentifier) {
    std::string expr_str = "2 + unknown";

    try {
        Expression expr(expr_str, vars, funcs);
        FAIL() << "Expected std::runtime_error, but nothing was thrown";
    }
    catch (const std::runtime_error& e) {
        std::string msg = e.what();

        EXPECT_TRUE(msg.find("Unknown identifier") != std::string::npos)
            << "Message should mention the error type";
        EXPECT_TRUE(msg.find("'unknown'") != std::string::npos)
            << "Message should contain the bad variable name";
        EXPECT_TRUE(msg.find("^") != std::string::npos)
            << "Message should contain an error pointer";
    }
}

TEST_F(ExpressionTest, ThrowsOnMismatchedBrackets_MissingClosing) {
    std::string expr_str = "(x + 5";
    try {
        Expression expr(expr_str, vars, funcs);
        FAIL() << "Expected std::runtime_error (Mismatched brackets)";
    }
    catch (const std::runtime_error& e) {
        std::string msg = e.what();

        EXPECT_TRUE(msg.find("Mismatched brackets") != std::string::npos);
        EXPECT_TRUE(msg.find("missing ')'") != std::string::npos);
        EXPECT_TRUE(msg.find("^") != std::string::npos);
    }
}

TEST_F(ExpressionTest, ThrowsOnMismatchedBrackets_MissingOpening) {
    std::string expr_str = "x + 5)";
    try {
        Expression expr(expr_str, vars, funcs);
        FAIL() << "Expected std::runtime_error (Mismatched brackets)";
    }
    catch (const std::runtime_error& e) {
        std::string msg = e.what();

        EXPECT_TRUE(msg.find("Mismatched brackets") != std::string::npos);
        EXPECT_TRUE(msg.find("^") != std::string::npos);
    }
}

TEST_F(ExpressionTest, ThrowsOnSyntaxError_TwoOperators) {
    std::string expr_str = "x + * y";
    try {
        Expression expr(expr_str, vars, funcs);
        FAIL() << "Expected std::runtime_error (Syntax Error)";
    }
    catch (const std::runtime_error& e) {
        std::string msg = e.what();

        EXPECT_TRUE(msg.find("Syntax Error") != std::string::npos);
        EXPECT_TRUE(msg.find("'*'") != std::string::npos);
        EXPECT_TRUE(msg.find("^") != std::string::npos);
    }
}

TEST_F(ExpressionTest, ThrowsOnEmptyBrackets) {
    std::string expr_str = "()";
    try {
        Expression expr(expr_str, vars, funcs);
        FAIL() << "Expected std::runtime_error (Syntax Error)";
    }
    catch (const std::runtime_error& e) {
        std::string msg = e.what();

        EXPECT_TRUE(msg.find("Syntax Error") != std::string::npos);
        EXPECT_TRUE(msg.find("')'") != std::string::npos);
        EXPECT_TRUE(msg.find("^") != std::string::npos);
    }
}

TEST_F(ExpressionTest, ThrowsOnFunctionWithoutBrackets) {
    std::string expr_str = "sin + 5";
    try {
        Expression expr(expr_str, vars, funcs);
        FAIL() << "Expected std::runtime_error (Syntax Error)";
    }
    catch (const std::runtime_error& e) {
        std::string msg = e.what();

        EXPECT_TRUE(msg.find("Syntax Error") != std::string::npos);
        EXPECT_TRUE(msg.find("'+'") != std::string::npos);
        EXPECT_TRUE(msg.find("^") != std::string::npos);
    }
}

TEST_F(ExpressionTest, CalculateSimple) {
    Expression expr("2 + 2 * 2", vars, funcs);
    // double нужно сравнивать через ASSERT_DOUBLE_EQ или ASSERT_NEAR
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 6.0);
}

TEST_F(ExpressionTest, CalculateDivision) {
    Expression expr("10 / 2", vars, funcs);
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 5.0);
}

TEST_F(ExpressionTest, CalculateVariables) {
    // x=10, y=20
    Expression expr("x + y", vars, funcs);
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 30.0);
}

TEST_F(ExpressionTest, CalculateFunctions) {
    // sin(0) = 0
    Expression expr("sin(0)", vars, funcs);
    ASSERT_NEAR(expr.calculate(vars, funcs), 0.0, 1e-9);
}

TEST_F(ExpressionTest, CalculateDivisionByZero) {
    Expression expr("5 / 0", vars, funcs);
    EXPECT_THROW(expr.calculate(vars, funcs), std::runtime_error);
}

// 1. Простой модуль: |x| -> x abs
TEST_F(ExpressionTest, SimpleModuleRPN) {
    Expression expr("| x |", vars, funcs);
    // Проверяем, что палки превратились в оператор abs
    ASSERT_EQ("RPN: [ x abs ]", expr.to_postfix_string());
}

// 2. Вычисление простого модуля
TEST_F(ExpressionTest, SimpleModuleCalculation) {
    // | -5 | = 5
    Expression expr("| -5 |", vars, funcs);
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 5.0);
}

// 3. Модуль от выражения: | 2 - 5 | -> 2 5 - abs
TEST_F(ExpressionTest, ModuleOfExpression) {
    // | 2 - 5 | = |-3| = 3
    Expression expr("| 2 - 5 |", vars, funcs);
    ASSERT_EQ("RPN: [ 2 5 - abs ]", expr.to_postfix_string());
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 3.0);
}

// 4. Вложенный модуль: ||x|| -> x abs abs
TEST_F(ExpressionTest, NestedModuleRPN) {
    Expression expr("| | x | |", vars, funcs);
    ASSERT_EQ("RPN: [ x abs abs ]", expr.to_postfix_string());
}

// 5. Сложный вложенный модуль
TEST_F(ExpressionTest, ComplexNestedModuleCalculation) {
    // Вычисляем: | 3 - | 10 - 20 | |
    // 1. | 10 - 20 | = |-10| = 10
    // 2. | 3 - 10 | = |-7| = 7
    Expression expr("| 3 - | 10 - 20 | |", vars, funcs);
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 7.0);
}

// 6. Модуль в составе формулы
TEST_F(ExpressionTest, ModuleMixedWithOperators) {
    // 2 * |-3| = 2 * 3 = 6
    Expression expr("2 * | -3 |", vars, funcs);
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 6.0);
}

// 7. Незакрытый модуль (открывающая палка есть, закрывающей нет)
TEST_F(ExpressionTest, ErrorMissingClosingPipe) {
    // | 5
    // ^
    try {
        Expression expr("| 5", vars, funcs);
        FAIL() << "Expected error for missing closing pipe";
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Mismatched brackets") != std::string::npos);
        // Должен указывать на начало
        EXPECT_TRUE(msg.find("^") != std::string::npos);
    }
}

// 8. Пересечение скобок (начали круглой, закончили палкой)
TEST_F(ExpressionTest, ErrorMixedBracketsRoundToPipe) {
    // ( 5 |
    //     ^
    try {
        Expression expr("( 5 |", vars, funcs);
        FAIL() << "Expected error for mixed brackets";
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Mismatched brackets") != std::string::npos);
        // Сообщение должно говорить, что ожидали ')', а нашли '|'
        EXPECT_TRUE(msg.find("'('") != std::string::npos);
    }
}

// 9. Пересечение скобок (начали палкой, закончили круглой)
TEST_F(ExpressionTest, ErrorMixedBracketsPipeToRound) {
    // | 5 )
    //     ^
    try {
        Expression expr("| 5 )", vars, funcs);
        FAIL() << "Expected error for mixed brackets";
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Mismatched brackets") != std::string::npos);
        // Сообщение должно говорить, что ожидали '|', а нашли ')'
        EXPECT_TRUE(msg.find("'|'") != std::string::npos);
    }
}
