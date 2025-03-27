//
// Created by ephir on 17.03.2025.
//

#ifndef CONSTANTEXPRESSION_H
#define CONSTANTEXPRESSION_H
#include "Expression.h"


struct ConstantExpression final : public Expression {
    ConstantExpression();
    explicit ConstantExpression(double_t value);
    ConstantExpression(const ConstantExpression& other);
    ConstantExpression(ConstantExpression&& other) noexcept;

    ConstantExpression& operator=(double_t value);
    ConstantExpression& operator=(const ConstantExpression& other);
    ConstantExpression& operator=(ConstantExpression&& other) noexcept;

    [[nodiscard]] std::unique_ptr<Expression> clone() const override;

    [[nodiscard]] double_t evaluate(std::map<std::string, double_t> values) const override;
    [[nodiscard]] std::unique_ptr<Expression> differentiate(std::string_view) const override;

    [[nodiscard]] std::string to_string() const override;

    ~ConstantExpression() noexcept override = default;

    friend struct ConstantExpressionTests;

    friend struct Parser;

protected:
    [[nodiscard]] bool equals(const Expression& other) const override;

private:
    double_t value;
};


#endif //CONSTANTEXPRESSION_H
