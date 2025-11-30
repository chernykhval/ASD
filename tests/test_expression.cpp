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
