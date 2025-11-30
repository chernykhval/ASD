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
    size_t _pos;

    Lexeme() : _type(LexemeType::Start), _value(""), _pos(0) {}
    Lexeme(LexemeType type, std::string value, size_t pos) :
    _type(type), _value(value), _pos(pos) {}
    Lexeme(LexemeType type, char value, size_t pos) :
    _type(type), _value(1, value), _pos(pos) {}
};

#endif  // LIBS_LIB_LEXEME_LEXEME_H_
