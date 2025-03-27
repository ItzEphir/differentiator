//
// Created by ephir on 27.03.2025.
//

#include "../include/ExponentExpression.h"

#include "../include/PlusExpression.h"
#include <cmath>

#include "../include/MultiplyExpression.h"


ExponentExpression::ExponentExpression(): target(nullptr) {}

ExponentExpression::ExponentExpression(std::unique_ptr<Expression> target): target(std::move(target)) {}

ExponentExpression::ExponentExpression(const ExponentExpression& other): target(other.target->clone()) {}

ExponentExpression::ExponentExpression(ExponentExpression&& other) noexcept: target(std::move(other.target)) {}

std::string ExponentExpression::to_string() const {
    if (target == nullptr) return "exp";
    const auto target_string = target->to_string();
    if (target_string.empty()) {
        return "";
    }
    if (target_string == "0") return "1";
    return "exp(" + target_string + ")";
}

ExponentExpression& ExponentExpression::operator=(const ExponentExpression& other) {
    target = std::move(other.target->clone());
    return *this;
}

ExponentExpression& ExponentExpression::operator=(ExponentExpression&& other) noexcept {
    target = std::move(other.target);
    return *this;
}

std::unique_ptr<Expression> ExponentExpression::clone() const {
    return std::make_unique<ExponentExpression>(*this);
}

double_t ExponentExpression::evaluate(const std::map<std::string, double_t> values) const {
    const auto leftResult = target->evaluate(values);
    return exp(leftResult);
}

std::unique_ptr<Expression> ExponentExpression::differentiate(const std::string_view variable) const {
    return std::make_unique<MultiplyExpression>(
        target->differentiate(variable),
        this->clone()
    );
}

bool ExponentExpression::equals(const Expression& other) const {
    const auto& other_casted = dynamic_cast<const ExponentExpression&>(other);
    if (this->target == nullptr) {
        return other_casted.target == nullptr;
    }
    if (other_casted.target == nullptr) {
        return this->target == nullptr;
    }
    return *this->target == *other_casted.target;
}
