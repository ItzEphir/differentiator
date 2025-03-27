//
// Created by ephir on 27.03.2025.
//

#include "../include/UnaryMinusExpression.h"

#include "../include/PlusExpression.h"
#include <cmath>
#include <valarray>

#include "../include/ConstantExpression.h"
#include "../include/CosExpression.h"
#include "../include/ExponentExpression.h"
#include "../include/LnExpression.h"
#include "../include/LogExpression.h"
#include "../include/MinusExpression.h"
#include "../include/PowerExpression.h"
#include "../include/SinExpression.h"
#include "../include/ValueExpression.h"

UnaryMinusExpression::UnaryMinusExpression(): target(nullptr) {}

UnaryMinusExpression::UnaryMinusExpression(std::unique_ptr<Expression> target): target(std::move(target)) {}

UnaryMinusExpression::UnaryMinusExpression(const UnaryMinusExpression& other): target(other.target->clone()) {}

UnaryMinusExpression::UnaryMinusExpression(UnaryMinusExpression&& other) noexcept: target(std::move(other.target)) {}

UnaryMinusExpression& UnaryMinusExpression::operator=(const UnaryMinusExpression& other) {
    target = std::move(other.target->clone());
    return *this;
}

UnaryMinusExpression& UnaryMinusExpression::operator=(UnaryMinusExpression&& other) noexcept {
    target = std::move(other.target);
    return *this;
}

std::string UnaryMinusExpression::to_string() const {
    if (target == nullptr) return "-";
    if (const auto* constant_expression = dynamic_cast<ConstantExpression*>(target.get())) {
        const auto str = constant_expression->to_string();
        if (str.empty()) return "";
        if (str == "0") return "0";
        return "-" + str;
    }
    if (const auto* value_expression = dynamic_cast<ValueExpression*>(target.get())) {
        const auto str = value_expression->to_string();
        if (str.empty()) return "";
        if (str == "0") return "0";
        return "-" + str;
    }
    if (const auto* plus_expression = dynamic_cast<PlusExpression*>(target.get())) {
        return MinusExpression(plus_expression->get_left(), plus_expression->get_right()).to_string();
    }
    if (const auto* minus_expression = dynamic_cast<MinusExpression*>(target.get())) {
        return PlusExpression(minus_expression->get_left(), minus_expression->get_right()).to_string();
    }
    if (const auto* sin_expression = dynamic_cast<SinExpression*>(target.get())) {
        const auto str = sin_expression->to_string();
        if (str.empty()) return "";
        if (str == "0") return "0";
        return "-" + str;
    }
    if (const auto* cos_expression = dynamic_cast<CosExpression*>(target.get())) {
        const auto str = cos_expression->to_string();
        if (str.empty()) return "";
        if (str == "0") return "0";
        return "-" + str;
    }
    if (const auto* ln_expression = dynamic_cast<LnExpression*>(target.get())) {
        const auto str = ln_expression->to_string();
        if (str.empty()) return "";
        if (str == "0") return "0";
        return "-" + str;
    }
    if (const auto* exp_expression = dynamic_cast<ExponentExpression*>(target.get())) {
        const auto str = exp_expression->to_string();
        if (str.empty()) return "";
        if (str == "0") return "0";
        return "-" + str;
    }
    if (const auto* log_expression = dynamic_cast<LogExpression*>(target.get())) {
        const auto str = log_expression->to_string();
        if (str.empty()) return "";
        if (str == "0") return "0";
        return "-" + str;
    }
    if (const auto* power_expression = dynamic_cast<PowerExpression*>(target.get())) {
        const auto str = power_expression->to_string();
        if (str.empty()) return "";
        if (str == "0") return "0";
        return "-" + str;
    }

    const auto str = target->to_string();
    if (str.empty()) return "";
    if (str == "0") return "0";
    if (str.starts_with("-")) return str.substr(1);
    return "-(" + str + ")";
}

std::unique_ptr<Expression> UnaryMinusExpression::clone() const {
    return std::make_unique<UnaryMinusExpression>(*this);
}

double_t UnaryMinusExpression::evaluate(const std::map<std::string, double_t> values) const {
    const auto target_result = target->evaluate(values);
    return -target_result;
}

std::unique_ptr<Expression> UnaryMinusExpression::differentiate(const std::string_view variable) const {
    return std::make_unique<UnaryMinusExpression>(target->differentiate(variable));
}

bool UnaryMinusExpression::equals(const Expression& other) const {
    const auto& other_casted = dynamic_cast<const UnaryMinusExpression&>(other);
    if (this->target == nullptr) {
        return other_casted.target == nullptr;
    }
    if (other_casted.target == nullptr) {
        return this->target == nullptr;
    }
    return *this->target == *other_casted.target;
}
