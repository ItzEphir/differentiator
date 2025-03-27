#ifndef PARSER_H
#define PARSER_H

#include "Expression.h"
#include <string>
#include <memory>
#include <stdexcept>

class Parser {
public:
    static std::unique_ptr<Expression> parse(const std::string& expression);
    
private:
    static std::unique_ptr<Expression> parseExpression(const std::string& expression, size_t& pos);
    static std::unique_ptr<Expression> parseTerm(const std::string& expression, size_t& pos);
    static std::unique_ptr<Expression> parseFactor(const std::string& expression, size_t& pos);
    static std::unique_ptr<Expression> parsePrimary(const std::string& expression, size_t& pos);
    static std::unique_ptr<Expression> parseFunction(const std::string& expression, size_t& pos);
    static std::unique_ptr<Expression> parseNumber(const std::string& expression, size_t& pos);
    static std::unique_ptr<Expression> parseVariable(const std::string& expression, size_t& pos);
    
    static void skipWhitespace(const std::string& expression, size_t& pos);
    static bool isOperator(char c);
    static bool isFunction(const std::string& expression, size_t pos);
    static std::string getFunctionName(const std::string& expression, size_t& pos);
};

#endif // PARSER_H 