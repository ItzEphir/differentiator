//
// Created by ephir on 27.03.2025.
//

#ifndef DIVIDEEXPRESSION_H
#define DIVIDEEXPRESSION_H
#include "Expression.h"

struct DivideExpression final : public Expression {
    DivideExpression();
    DivideExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);

    DivideExpression(const DivideExpression& other);
    DivideExpression(DivideExpression&& other) noexcept;

    [[nodiscard]] std::string to_string() const override;

    DivideExpression& operator=(const DivideExpression& other);
    DivideExpression& operator=(DivideExpression&& other) noexcept;

    [[nodiscard]] std::unique_ptr<Expression> clone() const override;

    [[nodiscard]] double_t evaluate(std::map<std::string, double_t> values) const override;
    [[nodiscard]] std::unique_ptr<Expression> differentiate(std::string_view variable) const override;

    friend struct DivideExpressionTests;

    friend struct Parser;

protected:
    [[nodiscard]] bool equals(const Expression& other) const override;

private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    static std::string part_to_string(const std::unique_ptr<Expression>&);
};

#endif //DIVIDEEXPRESSION_H
