#include "../include/Parser.h"
#include "../include/ConstantExpression.h"
#include "../include/ValueExpression.h"
#include "../include/PlusExpression.h"
#include "../include/MinusExpression.h"
#include "../include/MultiplyExpression.h"
#include "../include/DivideExpression.h"
#include "../include/SinExpression.h"
#include "../include/CosExpression.h"
#include "../include/LnExpression.h"
#include "../include/UnaryMinusExpression.h"
#include <cctype>

std::unique_ptr<Expression> Parser::parse(const std::string& expression) {
    size_t pos = 0;
    auto result = parseExpression(expression, pos);
    skipWhitespace(expression, pos);
    if (pos < expression.length()) {
        throw std::runtime_error("Unexpected characters at end of expression");
    }
    return result;
}

std::unique_ptr<Expression> Parser::parseExpression(const std::string& expression, size_t& pos) {
    skipWhitespace(expression, pos);

    // Handle unary minus
    if (pos < expression.length() && expression[pos] == '-') {
        pos++;
        skipWhitespace(expression, pos);
        auto expr = parseTerm(expression, pos);
        return std::make_unique<UnaryMinusExpression>(std::move(expr));
    }

    auto left = parseTerm(expression, pos);

    while (pos < expression.length()) {
        skipWhitespace(expression, pos);
        if (pos >= expression.length()) break;

        char op = expression[pos];
        if (op != '+' && op != '-') break;

        pos++;
        skipWhitespace(expression, pos);

        auto right = parseTerm(expression, pos);
        if (op == '+') {
            left = std::make_unique<PlusExpression>(std::move(left), std::move(right));
        } else {
            left = std::make_unique<MinusExpression>(std::move(left), std::move(right));
        }
    }

    return left;
}

std::unique_ptr<Expression> Parser::parseTerm(const std::string& expression, size_t& pos) {
    auto left = parseFactor(expression, pos);

    while (pos < expression.length()) {
        skipWhitespace(expression, pos);
        if (pos >= expression.length()) break;

        char op = expression[pos];
        if (op != '*' && op != '/') break;

        pos++;
        skipWhitespace(expression, pos);

        auto right = parseFactor(expression, pos);
        if (op == '*') {
            left = std::make_unique<MultiplyExpression>(left->clone(), right->clone());
        } else {
            left = std::make_unique<DivideExpression>(left->clone(), right->clone());
        }
    }

    return left;
}

std::unique_ptr<Expression> Parser::parseFactor(const std::string& expression, size_t& pos) {
    skipWhitespace(expression, pos);

    if (pos >= expression.length()) {
        throw std::runtime_error("Unexpected end of expression");
    }

    if (expression[pos] == '(') {
        pos++;
        auto expr = parseExpression(expression, pos);
        skipWhitespace(expression, pos);
        if (pos >= expression.length() || expression[pos] != ')') {
            throw std::runtime_error("Expected closing parenthesis");
        }
        pos++;
        return expr;
    }

    if (isFunction(expression, pos)) {
        return parseFunction(expression, pos);
    }

    if (std::isdigit(expression[pos]) || expression[pos] == '.') {
        return parseNumber(expression, pos);
    }

    if (std::isalpha(expression[pos])) {
        return parseVariable(expression, pos);
    }

    if (expression[pos] == '-') {
        pos++;
        skipWhitespace(expression, pos);
        auto expr = parseFactor(expression, pos);
        return std::make_unique<UnaryMinusExpression>(std::move(expr));
    }

    throw std::runtime_error("Unexpected character '" + std::string(1, expression[pos]) + "' in expression");
}

std::unique_ptr<Expression> Parser::parsePrimary(const std::string& expression, size_t& pos) {
    skipWhitespace(expression, pos);

    if (std::isdigit(expression[pos]) || expression[pos] == '.') {
        return parseNumber(expression, pos);
    }

    if (std::isalpha(expression[pos])) {
        return parseVariable(expression, pos);
    }

    throw std::runtime_error("Expected number or variable");
}

std::unique_ptr<Expression> Parser::parseFunction(const std::string& expression, size_t& pos) {
    std::string funcName = getFunctionName(expression, pos);
    skipWhitespace(expression, pos);

    if (pos >= expression.length() || expression[pos] != '(') {
        throw std::runtime_error("Expected opening parenthesis after function name");
    }
    pos++;
    skipWhitespace(expression, pos);

    if (pos >= expression.length() || expression[pos] == ')') {
        throw std::runtime_error("Empty function argument");
    }

    auto arg = parseExpression(expression, pos);
    skipWhitespace(expression, pos);

    if (pos >= expression.length() || expression[pos] != ')') {
        throw std::runtime_error("Expected closing parenthesis");
    }
    pos++;

    if (funcName == "sin") {
        return std::make_unique<SinExpression>(std::move(arg));
    } else if (funcName == "cos") {
        return std::make_unique<CosExpression>(std::move(arg));
    } else if (funcName == "ln") {
        return std::make_unique<LnExpression>(std::move(arg));
    } else {
        throw std::runtime_error("Unknown function: " + funcName);
    }
}

std::unique_ptr<Expression> Parser::parseNumber(const std::string& expression, size_t& pos) {
    size_t start = pos;
    bool hasDecimal = false;

    while (pos < expression.length()) {
        if (std::isdigit(expression[pos])) {
            pos++;
        } else if (expression[pos] == '.' && !hasDecimal) {
            hasDecimal = true;
            pos++;
        } else {
            break;
        }
    }

    std::string numberStr = expression.substr(start, pos - start);
    try {
        double value = std::stod(numberStr);
        return std::make_unique<ConstantExpression>(value);
    } catch (const std::exception&) {
        throw std::runtime_error("Invalid number format");
    }
}

std::unique_ptr<Expression> Parser::parseVariable(const std::string& expression, size_t& pos) {
    size_t start = pos;
    while (pos < expression.length() && (std::isalnum(expression[pos]) || expression[pos] == '_')) {
        pos++;
    }

    std::string varName = std::string(expression.substr(start, pos - start));
    return std::make_unique<ValueExpression>(varName);
}

void Parser::skipWhitespace(const std::string& expression, size_t& pos) {
    while (pos < expression.length() && std::isspace(expression[pos])) {
        pos++;
    }
}

bool Parser::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool Parser::isFunction(const std::string& expression, size_t pos) {
    std::string funcNames[] = {"sin", "cos", "log", "ln"};
    for (const auto& name : funcNames) {
        if (expression.substr(pos, name.length()) == name) {
            return true;
        }
    }
    return false;
}

std::string Parser::getFunctionName(const std::string& expression, size_t& pos) {
    size_t start = pos;
    while (pos < expression.length() && std::isalpha(expression[pos])) {
        pos++;
    }
    return expression.substr(start, pos - start);
}
