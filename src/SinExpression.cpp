//
// Created by ephir on 27.03.2025.
//

#include "../include/SinExpression.h"

#include "../include/PlusExpression.h"
#include <cmath>

#include "../include/CosExpression.h"
#include "../include/MultiplyExpression.h"

SinExpression::SinExpression(): target(nullptr) {}

SinExpression::SinExpression(std::unique_ptr<Expression> target): target(std::move(target)) {}

SinExpression::SinExpression(const SinExpression& other): target(other.target->clone()) {}

SinExpression::SinExpression(SinExpression&& other) noexcept: target(std::move(other.target)) {}

SinExpression& SinExpression::operator=(const SinExpression& other) {
    target = std::move(other.target->clone());
    return *this;
}

SinExpression& SinExpression::operator=(SinExpression&& other) noexcept {
    target = std::move(other.target);
    return *this;
}

std::string SinExpression::to_string() const {
    if (target == nullptr) return "sin";
    const auto target_string = target->to_string();
    if (target_string.empty()) {
        return "";
    }
    if (target_string == "0") {
        return "0";
    }
    return "sin(" + target_string + ")";
}

std::unique_ptr<Expression> SinExpression::clone() const {
    return std::make_unique<SinExpression>(*this);
}

double_t SinExpression::evaluate(const std::map<std::string, double_t> values) const {
    const auto target_result = target->evaluate(values);
    return sin(target_result);
}

std::unique_ptr<Expression> SinExpression::differentiate(const std::string_view variable) const {
    return std::make_unique<MultiplyExpression>(
        target->differentiate(variable),
        std::make_unique<CosExpression>(target->clone())
    );
}

bool SinExpression::equals(const Expression& other) const {
    const auto& other_casted = dynamic_cast<const SinExpression&>(other);
    if (this->target == nullptr) {
        return other_casted.target == nullptr;
    }
    if (other_casted.target == nullptr) {
        return this->target == nullptr;
    }
    return *this->target == *other_casted.target;
}
