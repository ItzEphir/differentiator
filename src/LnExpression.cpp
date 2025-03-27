//
// Created by ephir on 27.03.2025.
//

#include "../include/LnExpression.h"

#include "../include/PlusExpression.h"
#include <cmath>

#include "../include/DivideExpression.h"


LnExpression::LnExpression(): target(nullptr) {}

LnExpression::LnExpression(std::unique_ptr<Expression> target): target(std::move(target)) {}

LnExpression::LnExpression(const LnExpression& other): target(other.target->clone()) {}

LnExpression::LnExpression(LnExpression&& other) noexcept: target(std::move(other.target)) {}

LnExpression& LnExpression::operator=(const LnExpression& other) {
    target = std::move(other.target->clone());
    return *this;
}

LnExpression& LnExpression::operator=(LnExpression&& other) noexcept {
    target = std::move(other.target);
    return *this;
}

std::string LnExpression::to_string() const {
    if (target == nullptr) return "ln";
    const auto target_string = target->to_string();
    if (target_string.empty()) {
        return "";
    }
    if (target_string == "1") {
        return "0";
    }
    return "ln(" + target_string + ")";
}

std::unique_ptr<Expression> LnExpression::clone() const {
    return std::make_unique<LnExpression>(*this);
}

double_t LnExpression::evaluate(const std::map<std::string, double_t> values) const {
    const auto target_result = target->evaluate(values);
    return log(target_result);
}

std::unique_ptr<Expression> LnExpression::differentiate(const std::string_view variable) const {
    return std::make_unique<DivideExpression>(
        target->differentiate(variable),
        target->clone()
    );
}

bool LnExpression::equals(const Expression& other) const {
    const auto& other_casted = dynamic_cast<const LnExpression&>(other);
    if (this->target == nullptr) {
        return other_casted.target == nullptr;
    }
    if (other_casted.target == nullptr) {
        return this->target == nullptr;
    }
    return *this->target == *other_casted.target;
}
