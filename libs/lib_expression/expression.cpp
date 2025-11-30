// Copyright 2025 Chernykh Valentin

#include <string>
#include <sstream>
#include "libs/lib_expression/expression.h"
#include "libs/lib_stack/stack.h"

const bool Expression::Transitions[TypeCount][TypeCount] = {
    { 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0 },
    { 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0 },
    { 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

Expression::Expression(const std::string& expression,
 const VarTable& vars, const FunctionTable& funcs) :
_expression(expression) {
    tokenize();
    parse(vars, funcs);
}

std::string Expression::to_postfix_string() const noexcept {
    std::string result = "RPN: [ ";
    for (const auto& lex : _lexemes) {
        if (lex._type == LexemeType::UnaryOperator) {
            result += "u";
            result += lex._value;
            result += " ";
        } else {
            result += lex._value;
            result += " ";
        }
    }

    result += "]";

    return result;
}

bool Expression::can_transition(LexemeType from, LexemeType to) {
    return Transitions[static_cast<int>(from)][static_cast<int>(to)];
}

int Expression::get_priority(const Lexeme& lexeme) const {
    if (lexeme._type == LexemeType::Function) {
        return 5;
    }

    if (lexeme._type == LexemeType::UnaryOperator) {
        return 4;
    }

    if (lexeme._type == LexemeType::BinaryOperator) {
        if (lexeme._value == "^") return 3;
        if (lexeme._value == "*" || lexeme._value == "/") return 2;
        if (lexeme._value == "+" || lexeme._value == "-") return 1;
    }

    return 0;
}

bool Expression::is_matching_pair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

std::string Expression::create_error_message(size_t pos, const std::string& message) const {
    std::stringstream ss;

    ss << message << "\n";
    ss << _expression << "\n";

    for (size_t i = 0; i < pos; ++i) {
        ss << " ";
    }

    ss << "^";

    return ss.str();
}

void Expression::tokenize() {
    size_t i = 0;
    size_t len = _expression.length();

    while (i < len) {
        char current = _expression[i];

        if (current == ' ') {
            i++;
            continue;
        }

        size_t start_pos = i;

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

            _lexemes.push_back(Lexeme(LexemeType::Number, buffer, start_pos));
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

            _lexemes.push_back(Lexeme(LexemeType::Identifier, buffer, start_pos));

            continue;
        }

        switch (current) {
            case '(':
            case '[':
            case '{':
                _lexemes.push_back(Lexeme(LexemeType::LeftBracket, current, start_pos));
                i++;
                break;

            case ')':
            case ']':
            case '}':
                _lexemes.push_back(Lexeme(LexemeType::RightBracket, current, start_pos));
                i++;
                break;

            case ',':
                _lexemes.push_back(Lexeme(LexemeType::Separator, current, start_pos));
                i++;
                break;

            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                _lexemes.push_back(Lexeme(LexemeType::Operator, current, start_pos));
                i++;
                break;

            default:
                throw std::runtime_error("Unknown symbol at pos " + std::to_string(i));
        }
    }
}

void Expression::parse(const VarTable& vars, const FunctionTable& funcs) {
    LexemeType prev = LexemeType::Start;
    LinkedList<Lexeme> result_postfix;
    Stack<Lexeme> stack(_lexemes.size());

    for (auto& lex : _lexemes) {
        if (lex._type == LexemeType::Identifier) {
            if (funcs.contains(lex._value)) {
                lex._type = LexemeType::Function;
            } else if (vars.contains(lex._value)) {
                lex._type = LexemeType::Variable;
            } else {
                throw std::runtime_error(create_error_message(lex._pos,
                    "Unknown identifier: '" + lex._value + "'"));
            }
        }

        if (lex._type == LexemeType::Operator) {
            bool is_unary_context = (prev == LexemeType::Start ||
                           prev == LexemeType::LeftBracket ||
                           prev == LexemeType::Separator ||
                           prev == LexemeType::BinaryOperator ||
                           prev == LexemeType::UnaryOperator);

            bool can_be_unary = lex._value == "-";

            if (is_unary_context && can_be_unary) {
                lex._type = LexemeType::UnaryOperator;
            } else {
                lex._type = LexemeType::BinaryOperator;
            }
        }

        if (!can_transition(prev, lex._type)) {
            throw std::runtime_error(create_error_message(lex._pos,
                "Syntax Error: Unexpected lexeme '" + lex._value + "'"));
        }

        if (prev == LexemeType::Function && lex._type == LexemeType::LeftBracket) {
            if (lex._value != "(") {
                throw std::runtime_error(create_error_message(lex._pos,
                    "Syntax Error: Functions must be called using '(', but found '" + lex._value + "'"));
            }
        }

        switch (lex._type) {
            case LexemeType::Number:
            case LexemeType::Variable:
                result_postfix.push_back(lex);
                break;

            case LexemeType::LeftBracket:
            case LexemeType::Function:
                stack.push(lex);
                break;

            case LexemeType::Separator:
                while (!stack.is_empty() && stack.top()._type != LexemeType::LeftBracket) {
                    result_postfix.push_back(stack.top());
                    stack.pop();
                }

                if (stack.is_empty())
                    throw std::runtime_error(create_error_message(lex._pos,
                        "Separator outside of brackets: '" + lex._value + "'"));
                break;

            case LexemeType::RightBracket:
            {
                while (!stack.is_empty() && stack.top()._type != LexemeType::LeftBracket) {
                    result_postfix.push_back(stack.top());
                    stack.pop();
                }

                if (stack.is_empty())
                    throw std::runtime_error(create_error_message(lex._pos,
                        "Mismatched brackets: unexpected '" + lex._value + "'"));\

                char open_сhar = stack.top()._value[0];
                char close_сhar = lex._value[0];

                if (!is_matching_pair(open_сhar, close_сhar)) {
                    throw std::runtime_error(create_error_message(lex._pos,
                        "Mismatched brackets: expected matching for '" + std::string(1, open_сhar) +
                        "', but found '" + std::string(1, close_сhar) + "'"));
                }

                stack.pop();

                if (!stack.is_empty() && stack.top()._type == LexemeType::Function) {
                    result_postfix.push_back(stack.top());
                    stack.pop();
                }
            }
                break;

            case LexemeType::BinaryOperator:
            case LexemeType::UnaryOperator:
            {
                bool is_right_associative = (lex._value == "^" ||
                    lex._type == LexemeType::UnaryOperator);

                while (!stack.is_empty() && stack.top()._type != LexemeType::LeftBracket) {
                    int top_priority = get_priority(stack.top());
                    int curr_priority = get_priority(lex);

                    if (is_right_associative) {
                        if (top_priority > curr_priority) {
                            result_postfix.push_back(stack.top());
                            stack.pop();
                        } else {
                            break;
                        }
                    } else {
                        if (top_priority >= curr_priority) {
                            result_postfix.push_back(stack.top());
                            stack.pop();
                        } else {
                            break;
                        }
                    }
                }

                stack.push(lex);
            }
                break;

            default:
                break;
        }

        prev = lex._type;
    }

    while (!stack.is_empty()) {
        Lexeme top = stack.top();

        if (top._type == LexemeType::LeftBracket || top._type == LexemeType::Function) {
            throw std::runtime_error(create_error_message(top._pos,
                "Mismatched brackets: missing ')'"));
        }

        result_postfix.push_back(stack.top());
        stack.pop();
    }

    if (!can_transition(prev, LexemeType::End)) {
        throw std::runtime_error(create_error_message(_expression.length(),
            "Unexpected end of expression"));
    }

    _lexemes = result_postfix;
}
