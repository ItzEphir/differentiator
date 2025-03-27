//
// Created by ephir on 27.03.2025.
//

#ifndef POWEREXPRESSION_H
#define POWEREXPRESSION_H
#include "Expression.h"

struct PowerExpression final : public Expression {
    PowerExpression();
    PowerExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);

    PowerExpression(const PowerExpression& other);
    PowerExpression(PowerExpression&& other) noexcept;

    PowerExpression& operator=(const PowerExpression& other);
    PowerExpression& operator=(PowerExpression&& other) noexcept;

    [[nodiscard]] std::string to_string() const override;

    [[nodiscard]] std::unique_ptr<Expression> clone() const override;

    [[nodiscard]] double_t evaluate(std::map<std::string, double_t> values) const override;
    [[nodiscard]] std::unique_ptr<Expression> differentiate(std::string_view variable) const override;

    friend struct PowerExpressionTests;

    friend struct Parser;

protected:
    [[nodiscard]] bool equals(const Expression& other) const override;

private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    static std::string part_to_string(const std::unique_ptr<Expression>&);
};

#endif //POWEREXPRESSION_H
