//
// Created by ephir on 27.03.2025.
//

#ifndef LOGEXPRESSION_H
#define LOGEXPRESSION_H
#include "Expression.h"

struct LogExpression final : public Expression {
    LogExpression();
    LogExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);

    LogExpression(const LogExpression& other);
    LogExpression(LogExpression&& other) noexcept;

    [[nodiscard]] std::string to_string() const override;

    LogExpression& operator=(const LogExpression& other);
    LogExpression& operator=(LogExpression&& other) noexcept;

    [[nodiscard]] std::unique_ptr<Expression> clone() const override;

    [[nodiscard]] double_t evaluate(std::map<std::string, double_t> values) const override;
    [[nodiscard]] std::unique_ptr<Expression> differentiate(std::string_view variable) const override;

    friend struct LogExpressionTests;

    friend struct Parser;

protected:
    [[nodiscard]] bool equals(const Expression& other) const override;

private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};

#endif //LOGEXPRESSION_H
