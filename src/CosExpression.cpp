//
// Created by ephir on 27.03.2025.
//

#include "../include/CosExpression.h"

#include "../include/PlusExpression.h"
#include <cmath>

#include "../include/DivideExpression.h"
#include "../include/MultiplyExpression.h"
#include "../include/SinExpression.h"
#include "../include/UnaryMinusExpression.h"


CosExpression::CosExpression(): target(nullptr) {}

CosExpression::CosExpression(std::unique_ptr<Expression> target): target(std::move(target)) {}

CosExpression::CosExpression(const CosExpression& other): target(other.target->clone()) {}

CosExpression::CosExpression(CosExpression&& other) noexcept: target(std::move(other.target)) {}

CosExpression& CosExpression::operator=(const CosExpression& other) {
    target = std::move(other.target->clone());
    return *this;
}

CosExpression& CosExpression::operator=(CosExpression&& other) noexcept {
    target = std::move(other.target);
    return *this;
}

std::string CosExpression::to_string() const {
    if (target == nullptr) return "cos";
    const auto target_string = target->to_string();
    if (target_string.empty()) {
        return "";
    }
    if (target_string == "0") {
        return "1";
    }
    return "cos(" + target_string + ")";
}

std::unique_ptr<Expression> CosExpression::clone() const {
    return std::make_unique<CosExpression>(*this);
}

double_t CosExpression::evaluate(const std::map<std::string, double_t> values) const {
    const auto target_result = target->evaluate(values);
    return cos(target_result);
}

std::unique_ptr<Expression> CosExpression::differentiate(const std::string_view variable) const {
    return std::make_unique<MultiplyExpression>(
        target->differentiate(variable),
        std::make_unique<UnaryMinusExpression>(std::make_unique<SinExpression>(target->clone()))
    );
}

bool CosExpression::equals(const Expression& other) const {
    const auto& other_casted = dynamic_cast<const CosExpression&>(other);
    if (this->target == nullptr) {
        return other_casted.target == nullptr;
    }
    if (other_casted.target == nullptr) {
        return this->target == nullptr;
    }
    return *this->target == *other_casted.target;
}
