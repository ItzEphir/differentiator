//
// Created by ephir on 27.03.2025.
//

#ifndef LNEXPRESSION_H
#define LNEXPRESSION_H
#include "Expression.h"


struct LnExpression final : public Expression {
    LnExpression();
    explicit LnExpression(std::unique_ptr<Expression> target);

    LnExpression(const LnExpression& other);
    LnExpression(LnExpression&& other) noexcept;

    LnExpression& operator=(const LnExpression& other);
    LnExpression& operator=(LnExpression&& other) noexcept;

    [[nodiscard]] std::string to_string() const override;

    [[nodiscard]] std::unique_ptr<Expression> clone() const override;

    [[nodiscard]] double_t evaluate(std::map<std::string, double_t> values) const override;
    [[nodiscard]] std::unique_ptr<Expression> differentiate(std::string_view variable) const override;

    friend struct LnExpressionTests;

    friend struct Parser;

protected:
    [[nodiscard]] bool equals(const Expression& other) const override;

private:
    std::unique_ptr<Expression> target;
};

#endif //LNEXPRESSION_H
