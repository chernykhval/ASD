// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_LEXEME_LEXEME_H_
#define LIBS_LIB_LEXEME_LEXEME_H_

#include <string>

enum class LexemeType {
    Constant,
    BinaryOperator,
    LeftBracket,
    RightBracket,
    Identifier,
    Variable
};

struct Lexeme {
    LexemeType _type;
    std::string _value;

    Lexeme(LexemeType type, std::string value) : _type(type), _value(value) {}
};

#endif  // LIBS_LIB_LEXEME_LEXEME_H_
