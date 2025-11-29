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
    static constexpr bool Transitions[TypeCount][TypeCount] = {
       { 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0 },
       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
       { 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
       { 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0 },
       { 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
       { 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0 },
       { 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0 },
       { 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0 },
       { 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
       { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

 public:
    explicit Expression(const std::string& expression);

 private:
    bool can_transition(LexemeType from, LexemeType to);
    int get_priority(const Lexeme& lexeme) const;
    void init_lexemes();
    void to_postfix(const VarTable& vars, const FunctionTable& funcs);
};

#endif  // LIBS_LIB_EXPRESSION_EXPRESSION_H_
