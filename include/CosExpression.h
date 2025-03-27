//
// Created by ephir on 27.03.2025.
//

#ifndef COSEXPRESSION_H
#define COSEXPRESSION_H
#include "Expression.h"


struct CosExpression final : public Expression {
    CosExpression();
    explicit CosExpression(std::unique_ptr<Expression> target);

    CosExpression(const CosExpression& other);
    CosExpression(CosExpression&& other) noexcept;

    CosExpression& operator=(const CosExpression& other);
    CosExpression& operator=(CosExpression&& other) noexcept;

    [[nodiscard]] std::string to_string() const override;

    [[nodiscard]] std::unique_ptr<Expression> clone() const override;

    [[nodiscard]] double_t evaluate(std::map<std::string, double_t> values) const override;
    [[nodiscard]] std::unique_ptr<Expression> differentiate(std::string_view variable) const override;

    friend struct CosExpressionTests;

    friend struct Parser;

protected:
    [[nodiscard]] bool equals(const Expression& other) const override;

private:
    std::unique_ptr<Expression> target;
};

#endif //COSEXPRESSION_H
