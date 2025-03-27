//
// Created by ephir on 27.03.2025.
//

#ifndef MINUSEXPRESSION_H
#define MINUSEXPRESSION_H
#include "Expression.h"

struct MinusExpression final : public Expression {
    MinusExpression();
    MinusExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);

    MinusExpression(const MinusExpression& other);
    MinusExpression(MinusExpression&& other) noexcept;

    MinusExpression& operator=(const MinusExpression& other);
    MinusExpression& operator=(MinusExpression&& other) noexcept;

    [[nodiscard]] std::string to_string() const override;

    [[nodiscard]] std::unique_ptr<Expression> clone() const override;

    [[nodiscard]] double_t evaluate(std::map<std::string, double_t> values) const override;
    [[nodiscard]] std::unique_ptr<Expression> differentiate(std::string_view variable) const override;

    [[nodiscard]] std::unique_ptr<Expression> get_left() const {
        return left->clone();
    }

    [[nodiscard]] std::unique_ptr<Expression> get_right() const {
        return right->clone();
    }

    friend struct MinusExpressionTests;

    friend struct Parser;

protected:
    [[nodiscard]] bool equals(const Expression& other) const override;

private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    static std::string part_to_string(const std::unique_ptr<Expression>&);
};

#endif //MINUSEXPRESSION_H
