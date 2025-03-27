//
// Created by ephir on 27.03.2025.
//

#ifndef UNARYMINUSEXPRESSION_H
#define UNARYMINUSEXPRESSION_H
#include "Expression.h"


struct UnaryMinusExpression final : public Expression {
    UnaryMinusExpression();
    explicit UnaryMinusExpression(std::unique_ptr<Expression> target);

    UnaryMinusExpression(const UnaryMinusExpression& other);
    UnaryMinusExpression(UnaryMinusExpression&& other) noexcept;

    UnaryMinusExpression& operator=(const UnaryMinusExpression& other);
    UnaryMinusExpression& operator=(UnaryMinusExpression&& other) noexcept;

    [[nodiscard]] std::string to_string() const override;

    [[nodiscard]] std::unique_ptr<Expression> clone() const override;

    [[nodiscard]] double_t evaluate(std::map<std::string, double_t> values) const override;
    [[nodiscard]] std::unique_ptr<Expression> differentiate(std::string_view variable) const override;

    friend struct UnaryMinusExpressionTests;

    friend struct Parser;

protected:
    [[nodiscard]] bool equals(const Expression& other) const override;

private:
    std::unique_ptr<Expression> target;
};


#endif //UNARYMINUSEXPRESSION_H
