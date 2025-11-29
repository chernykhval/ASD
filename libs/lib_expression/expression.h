// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_EXPRESSION_EXPRESSION_H_
#define LIBS_LIB_EXPRESSION_EXPRESSION_H_

#include <string>
#include "libs/lib_lexeme/lexeme.h"
#include "libs/lib_linked_list/linked_list.h"

class Expression {
 private:
    std::string _expression;
    LinkedList<Lexeme> _lexemes;

 public:
    explicit Expression(const std::string& expression);

 private:
    void init_lexemes();
};

#endif  // LIBS_LIB_EXPRESSION_EXPRESSION_H_
