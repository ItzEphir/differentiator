//
// Created by ephir on 27.03.2025.
//
#include "../include/LogExpression.h"

#include "../include/DivideExpression.h"
#include "../include/LnExpression.h"
#include "../include/MultiplyExpression.h"
#include "../include/PlusExpression.h"
#include "../include/ValueExpression.h"


LogExpression::LogExpression(): left(nullptr), right(nullptr) {}

LogExpression::LogExpression(std::unique_ptr<Expression> left,
                             std::unique_ptr<Expression> right): left(std::move(left)),
                                                                 right(std::move(right)) {}

LogExpression::LogExpression(const LogExpression& other) {
    left = std::move(other.left->clone());
    right = std::move(std::unique_ptr(other.right->clone()));
}

LogExpression::LogExpression(LogExpression&& other) noexcept: left(std::move(other.left)),
                                                              right(std::move(other.right)) {}

std::string LogExpression::to_string() const {
    if (left == nullptr || right == nullptr) return "log";
    const auto left_string = left->to_string();
    const auto right_string = right->to_string();
    if (left_string.empty() || right_string.empty()) {
        return "";
    }
    if (right_string == "1") {
        return "0";
    }
    return "log(" + left_string + "," + right_string + ")";
}

LogExpression& LogExpression::operator=(const LogExpression& other) {
    left = std::move(other.left->clone());
    right = std::move(std::unique_ptr(other.right->clone()));
    return *this;
}

LogExpression& LogExpression::operator=(LogExpression&& other) noexcept {
    left = std::move(other.left);
    right = std::move(other.right);
    return *this;
}

std::unique_ptr<Expression> LogExpression::clone() const {
    return std::make_unique<LogExpression>(*this);
}

double_t LogExpression::evaluate(const std::map<std::string, double_t> values) const {
    const auto leftResult = left->evaluate(values);
    const auto rightResult = right->evaluate(values);
    return log(rightResult) / log(leftResult);
}

std::unique_ptr<Expression> LogExpression::differentiate(const std::string_view variable) const {
    const auto divide_expression = DivideExpression(
        std::make_unique<LnExpression>(right->clone()),
        std::make_unique<LnExpression>(left->clone())
    );
    return divide_expression.differentiate(variable);
}

bool LogExpression::equals(const Expression& other) const {
    const auto& other_casted = dynamic_cast<const LogExpression&>(other);
    if (this->left == nullptr || other_casted.left == nullptr) {
        if (this->left != nullptr || other_casted.left != nullptr) {
            return false;
        }
    }
    if ((this->right == nullptr || other_casted.right == nullptr) &&
        (this->right != nullptr || other_casted.right != nullptr)) {
        return false;
    }
    if (this->left == nullptr && other_casted.left == nullptr &&
        this->right == nullptr && other_casted.right == nullptr) {
        return true;
    }
    return *this->left == *other_casted.left && *this->right == *other_casted.right;
}
