//
// Created by ephir on 17.03.2025.
//

#include "../include/ConstantExpression.h"

ConstantExpression::ConstantExpression(): value(0) {}

ConstantExpression::ConstantExpression(const double_t value): value(value) {}

ConstantExpression::ConstantExpression(const ConstantExpression& other): value(other.value) {}

ConstantExpression::ConstantExpression(ConstantExpression&& other) noexcept : value(other.value) {}

ConstantExpression& ConstantExpression::operator=(const double_t value) {
    this->value = value;
    return *this;
}

ConstantExpression& ConstantExpression::operator=(const ConstantExpression& other) {
    this->value = other.value;
    return *this;
}

ConstantExpression& ConstantExpression::operator=(ConstantExpression&& other) noexcept {
    this->value = other.value;
    return *this;
}

std::unique_ptr<Expression> ConstantExpression::clone() const {
    return std::make_unique<ConstantExpression>(*this);
}

double_t ConstantExpression::evaluate(std::map<std::string, double_t>) const {
    return this->value;
}

std::unique_ptr<Expression> ConstantExpression::differentiate(std::string_view) const {
    return std::make_unique<ConstantExpression>();
}

std::string ConstantExpression::to_string() const {
    if (value == 0) return "0";
    if (value == 1) return "1";
    return std::to_string(this->value);
}

bool ConstantExpression::equals(const Expression& other) const {
    const auto& other_casted = dynamic_cast<const ConstantExpression&>(other);
    return this->value == other_casted.value;
}
