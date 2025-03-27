//
// Created by ephir on 17.03.2025.
//

#include "../include/ValueExpression.h"

#include "../include/ConstantExpression.h"

ValueExpression::ValueExpression() = default;

ValueExpression::ValueExpression(const std::string name) {
    this->name = name;
}

ValueExpression::ValueExpression(const ValueExpression& other): name(std::string(other.name)) {}

ValueExpression::ValueExpression(ValueExpression&& other) noexcept: name(std::string(other.name)) {}

ValueExpression& ValueExpression::operator=(const ValueExpression& other) {
    this->name = std::string(other.name);
    return *this;
}

ValueExpression& ValueExpression::operator=(ValueExpression&& other) noexcept {
    this->name = std::string(other.name);
    return *this;
}

std::unique_ptr<Expression> ValueExpression::clone() const {
    auto result = std::make_unique<ValueExpression>();
    result->name = this->name;
    return result;
}

std::string ValueExpression::to_string() const {
    if (name.empty()) return "";
    return std::string(name);
}

double_t ValueExpression::evaluate(std::map<std::string, double_t> values) const {
    for (const auto& [name, value] : values) {
        if (name == this->name) {
            return value;
        }
    }
    throw std::invalid_argument("Value expression does not exist");
}

std::unique_ptr<Expression> ValueExpression::differentiate(const std::string_view name) const {
    if (name == this->name) {
        return std::make_unique<ConstantExpression>(1);
    }
    return std::make_unique<ConstantExpression>(0);
}

bool ValueExpression::equals(const Expression& other) const {
    const auto& other_casted = dynamic_cast<const ValueExpression&>(other);
    return this->name == other_casted.name;
}
