// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_LEXEME_LEXEME_H_
#define LIBS_LIB_LEXEME_LEXEME_H_

#include <string>

enum class LexemeType {
    Start,
    End,

    Number,
    LeftBracket,
    RightBracket,
    Separator,

    BinaryOperator,
    UnaryOperator,
    Variable,
    Function,

    Identifier,
    Operator,

    Count
};

struct Lexeme {
    LexemeType _type;
    std::string _value;

    Lexeme() : _type(LexemeType::Start), _value("") {}
    Lexeme(LexemeType type, std::string value) : _type(type), _value(value) {}
    Lexeme(LexemeType type, char value) : _type(type), _value(1, value) {}
};

#endif  // LIBS_LIB_LEXEME_LEXEME_H_
