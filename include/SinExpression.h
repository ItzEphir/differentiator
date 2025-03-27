//
// Created by ephir on 27.03.2025.
//

#ifndef SINEXPRESSION_H
#define SINEXPRESSION_H
#include "Expression.h"


struct SinExpression final : public Expression {
    SinExpression();
    explicit SinExpression(std::unique_ptr<Expression> target);

    SinExpression(const SinExpression& other);
    SinExpression(SinExpression&& other) noexcept;

    SinExpression& operator=(const SinExpression& other);
    SinExpression& operator=(SinExpression&& other) noexcept;

    [[nodiscard]] std::string to_string() const override;

    [[nodiscard]] std::unique_ptr<Expression> clone() const override;

    [[nodiscard]] double_t evaluate(std::map<std::string, double_t> values) const override;
    [[nodiscard]] std::unique_ptr<Expression> differentiate(std::string_view variable) const override;

    friend struct SinExpressionTests;

    friend struct Parser;

protected:
    [[nodiscard]] bool equals(const Expression& other) const override;

private:
    std::unique_ptr<Expression> target;
};

#endif //SINEXPRESSION_H
