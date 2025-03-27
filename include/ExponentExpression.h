//
// Created by ephir on 27.03.2025.
//

#ifndef EXPONENTEXPRESSION_H
#define EXPONENTEXPRESSION_H
#include "Expression.h"

struct ExponentExpression final : public Expression {
    ExponentExpression();
    explicit ExponentExpression(std::unique_ptr<Expression> target);

    ExponentExpression(const ExponentExpression& other);
    ExponentExpression(ExponentExpression&& other) noexcept;

    [[nodiscard]] std::string to_string() const override;

    ExponentExpression& operator=(const ExponentExpression& other);
    ExponentExpression& operator=(ExponentExpression&& other) noexcept;

    [[nodiscard]] std::unique_ptr<Expression> clone() const override;

    [[nodiscard]] double_t evaluate(std::map<std::string, double_t> values) const override;
    [[nodiscard]] std::unique_ptr<Expression> differentiate(std::string_view variable) const override;

    friend struct ExponentExpressionTests;

    friend struct Parser;

protected:
    [[nodiscard]] bool equals(const Expression& other) const override;

private:
    std::unique_ptr<Expression> target;
};

#endif //EXPONENTEXPRESSION_H
