// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include <cmath>
#include <string>
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
    Expression expr("x + y * 2", vars, funcs);
    ASSERT_EQ("RPN: [ x y 2 * + ]", expr.to_postfix_string());
}

TEST_F(ExpressionTest, BracketsChangePriority) {
    Expression expr("(x + y) * 2", vars, funcs);
    ASSERT_EQ("RPN: [ x y + 2 * ]", expr.to_postfix_string());
}

TEST_F(ExpressionTest, UnaryMinusAtStart) {
    Expression expr("-x + 5", vars, funcs);
    ASSERT_EQ("RPN: [ x u- 5 + ]", expr.to_postfix_string());
}

TEST_F(ExpressionTest, UnaryMinusInMiddle) {
    Expression expr("5 * -y", vars, funcs);
    ASSERT_EQ("RPN: [ 5 y u- * ]", expr.to_postfix_string());
}

TEST_F(ExpressionTest, Functions) {
    Expression expr("sin(x) + 1", vars, funcs);
    ASSERT_EQ("RPN: [ x sin 1 + ]", expr.to_postfix_string());
}

TEST_F(ExpressionTest, RightAssociativity) {
    Expression expr("- - x", vars, funcs);
    ASSERT_EQ("RPN: [ x u- u- ]", expr.to_postfix_string());
}

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
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 6.0);
}

TEST_F(ExpressionTest, CalculateDivision) {
    Expression expr("10 / 2", vars, funcs);
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 5.0);
}

TEST_F(ExpressionTest, CalculateVariables) {
    Expression expr("x + y", vars, funcs);
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 30.0);
}

TEST_F(ExpressionTest, CalculateFunctions) {
    Expression expr("sin(0)", vars, funcs);
    ASSERT_NEAR(expr.calculate(vars, funcs), 0.0, 1e-9);
}

TEST_F(ExpressionTest, CalculateDivisionByZero) {
    Expression expr("5 / 0", vars, funcs);
    EXPECT_THROW(expr.calculate(vars, funcs), std::runtime_error);
}

TEST_F(ExpressionTest, SimpleModuleRPN) {
    Expression expr("| x |", vars, funcs);
    ASSERT_EQ("RPN: [ x abs ]", expr.to_postfix_string());
}

TEST_F(ExpressionTest, SimpleModuleCalculation) {
    Expression expr("| -5 |", vars, funcs);
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 5.0);
}

TEST_F(ExpressionTest, ModuleOfExpression) {
    Expression expr("| 2 - 5 |", vars, funcs);
    ASSERT_EQ("RPN: [ 2 5 - abs ]", expr.to_postfix_string());
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 3.0);
}

TEST_F(ExpressionTest, NestedModuleRPN) {
    Expression expr("| | x | |", vars, funcs);
    ASSERT_EQ("RPN: [ x abs abs ]", expr.to_postfix_string());
}

TEST_F(ExpressionTest, ComplexNestedModuleCalculation) {
    Expression expr("| 3 - | 10 - 20 | |", vars, funcs);
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 7.0);
}

TEST_F(ExpressionTest, ModuleMixedWithOperators) {
    Expression expr("2 * | -3 |", vars, funcs);
    ASSERT_DOUBLE_EQ(expr.calculate(vars, funcs), 6.0);
}

TEST_F(ExpressionTest, ErrorMissingClosingPipe) {
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

TEST_F(ExpressionTest, ErrorMixedBracketsRoundToPipe) {
    try {
        Expression expr("( 5 |", vars, funcs);
        FAIL() << "Expected error for mixed brackets";
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Mismatched brackets") != std::string::npos);
        EXPECT_TRUE(msg.find("'('") != std::string::npos);
    }
}

TEST_F(ExpressionTest, ErrorMixedBracketsPipeToRound) {
    try {
        Expression expr("| 5 )", vars, funcs);
        FAIL() << "Expected error for mixed brackets";
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Mismatched brackets") != std::string::npos);
        EXPECT_TRUE(msg.find("'|'") != std::string::npos);
    }
}
