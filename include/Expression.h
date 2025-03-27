//
// Created by ephir on 17.03.2025.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <map>

struct Expression {
    virtual ~Expression() = default;
    [[nodiscard]] virtual double_t evaluate(std::map<std::string, double_t> values) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Expression> differentiate(std::string_view variable) const = 0;

    virtual bool operator==(const Expression& other) const {
        return (typeid(*this) == typeid(other)) && equals(other);
    }

    [[nodiscard]] virtual std::unique_ptr<Expression> clone() const = 0;

    [[nodiscard]] virtual std::string to_string() const = 0;

    friend struct Parser;

protected:
    [[nodiscard]] virtual bool equals(const Expression& other) const = 0;
};

#endif //EXPRESSION_H
