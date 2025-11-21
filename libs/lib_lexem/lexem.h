// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_LEXEM_LEXEM_H_
#define LIBS_LIB_LEXEM_LEXEM_H_

#include <string>

enum class LexemType {
    Constant,
    BinaryOperator,
    LeftBracket,
    RightBracket,
    Identifier,
    Variable
};

struct Lexem {
    LexemType type;
    std::string value;

    Lexem(LexemType type, std::string value) : type(type), value(value) {}
};

#endif  // LIBS_LIB_LEXEM_LEXEM_H_
