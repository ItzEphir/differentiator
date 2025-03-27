//
// Created by ephir on 27.03.2025.
//

#ifndef MULTIPLYEXPRESSION_H
#define MULTIPLYEXPRESSION_H
#include "Expression.h"

struct MultiplyExpression final : public Expression {
    MultiplyExpression();
    MultiplyExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);

    MultiplyExpression(const MultiplyExpression& other);
    MultiplyExpression(MultiplyExpression&& other) noexcept;

    MultiplyExpression& operator=(const MultiplyExpression& other);
    MultiplyExpression& operator=(MultiplyExpression&& other) noexcept;

    [[nodiscard]] std::string to_string() const override;

    [[nodiscard]] std::unique_ptr<Expression> clone() const override;

    [[nodiscard]] double_t evaluate(std::map<std::string, double_t> values) const override;
    [[nodiscard]] std::unique_ptr<Expression> differentiate(std::string_view variable) const override;

    friend struct MultiplyExpressionTests;

    friend struct Parser;

protected:
    [[nodiscard]] bool equals(const Expression& other) const override;

private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    [[nodiscard]] static std::string part_to_string(const std::unique_ptr<Expression>&);
};

#endif //MULTIPLYEXPRESSION_H
