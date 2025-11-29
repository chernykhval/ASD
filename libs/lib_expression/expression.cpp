// Copyright 2025 Chernykh Valentin

#include <string>
#include "libs/lib_expression/expression.h"

Expression::Expression(const std::string& expression) :
_expression(expression) {
}

void Expression::init_lexemes() {
    size_t i = 0;
    size_t len = _expression.length();

    while (i < len) {
        char current = _expression[i];

        if (current == ' ') {
            i++;
            continue;
        }

        if (current >= '0' && current <= '9') {
            std::string buffer;
            bool hasDot = false;

            while (i < len) {
                char c = _expression[i];

                if (c >= '0' && c <= '9') {
                    buffer += c;
                    i++;
                } else if (c == '.') {
                    if (hasDot) {
                        break;
                    }

                    hasDot = true;
                    buffer += c;
                    i++;
                } else {
                    break;
                }
            }

            _lexemes.push_back(Lexeme(LexemeType::Number, buffer));
            continue;
        }

        if (current >= 'a' && current <= 'z'
            || current >= 'A' && current <= 'Z' || current == '_') {
            std::string buffer;

            while (i < len && (_expression[i] >= 'a' && _expression[i] <= 'z'
                || _expression[i] >= 'A' && _expression[i] <= 'Z'
                || _expression[i] >= '0' && _expression[i] <= '9'||
                _expression[i] == '_')) {
                buffer += _expression[i];
                i++;
            }

            _lexemes.push_back(Lexeme(LexemeType::Identifier, buffer));

            continue;
        }

        switch (current) {
            case '(':
                _lexemes.push_back(Lexeme(LexemeType::LeftBracket, current));
                i++;
                break;

            case ')':
                _lexemes.push_back(Lexeme(LexemeType::RightBracket, current));
                i++;
                break;

            case ',':
                _lexemes.push_back(Lexeme(LexemeType::Separator, current));
                i++;
                break;

            case '+':
            case '-':
            case '*':
            case '/':
                _lexemes.push_back(Lexeme(LexemeType::Operator, current));
                i++;
                break;

            default:
                throw std::invalid_argument("Invalid symbol");
        }
    }
}

void Expression::to_postfix() {
    LexemeType prev = LexemeType::Start;

    for (auto it = _lexemes.begin(); it != _lexemes.end(); it++) {
        if (prev == LexemeType::Identifier) {
            switch (it->_type) {
                case LexemeType::LeftBracket:
                    (--it) -> _type = LexemeType::Function;
                    break;

                case LexemeType::End:
                case LexemeType::RightBracket:
                case LexemeType::Separator:
                case LexemeType::BinaryOperator:
                    (--it) -> _type = LexemeType::Variable;
                    break;
                break;

                default:
                    throw std::invalid_argument("Unknown identifier");
            }
        }

        if (it->_type == LexemeType::Operator && prev != LexemeType::Start) {
            switch (prev) {
                case LexemeType::Number:
                case LexemeType::RightBracket:
                case LexemeType::Variable:
                    it->_type = LexemeType::BinaryOperator;
                    break;

                case LexemeType::Start:
                case LexemeType::LeftBracket:
                case LexemeType::Separator:
                    it->_type = LexemeType::UnaryOperator;
                    break;

                default:
                    throw std::invalid_argument("Unknown operator type");;
            }
        }

        if (!can_transition(prev, it->_type)) {
            throw std::runtime_error("Error parsing...");
        }

        // Перевод в ОПН

        prev = it->_type;
    }
}

bool Expression::can_transition(LexemeType from, LexemeType to) {
    return Transitions[static_cast<int>(from)][static_cast<int>(to)];
}
