//
// Created by ephir on 17.03.2025.
//

#ifndef VALUEEXPRESSION_H
#define VALUEEXPRESSION_H
#include "Expression.h"


struct ValueExpression final : public Expression {
    ValueExpression();
    explicit ValueExpression(std::string name);
    ValueExpression(const ValueExpression& other);
    ValueExpression(ValueExpression&& other) noexcept;

    ValueExpression& operator=(const ValueExpression& other);
    ValueExpression& operator=(ValueExpression&& other) noexcept;

    [[nodiscard]] std::unique_ptr<Expression> clone() const override;

    [[nodiscard]] std::string to_string() const override;

    ~ValueExpression() override = default;

    [[nodiscard]] double_t evaluate(std::map<std::string, double_t> values) const override;
    [[nodiscard]] std::unique_ptr<Expression> differentiate(std::string_view) const override;

    [[nodiscard]] bool equals(const Expression& other) const override;

    friend struct ValueExpressionTests;

    friend struct Parser;

private:
    std::string name;
};


#endif //VALUEEXPRESSION_H
