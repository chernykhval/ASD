// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_EXPRESSION_EXPRESSION_H_
#define LIBS_LIB_EXPRESSION_EXPRESSION_H_

#include <string>
#include "libs/lib_lexeme/lexeme.h"
#include "libs/lib_linked_list/linked_list.h"
#include "libs/lib_var_table/var_table.h"
#include "libs/lib_function_table/function_table.h"

class Expression {
 private:
    std::string _expression;
    LinkedList<Lexeme> _lexemes;
    static constexpr int TypeCount = static_cast<int>(LexemeType::Count);
    static const bool Transitions[TypeCount][TypeCount];

 public:
    Expression() = default;
    Expression(const std::string& expression,
       const VarTable& vars, const FunctionTable& funcs);
    Expression(const Expression&) = default;
    Expression& operator=(const Expression&) = default;

    std::string to_postfix_string() const noexcept;

 private:
    bool can_transition(LexemeType from, LexemeType to);
    int get_priority(const Lexeme& lexeme) const;
    void tokenize();
    void parse(const VarTable& vars, const FunctionTable& funcs);
};

#endif  // LIBS_LIB_EXPRESSION_EXPRESSION_H_
