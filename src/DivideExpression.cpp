//
// Created by ephir on 27.03.2025.
//

#include "../include/DivideExpression.h"

#include "../include/ConstantExpression.h"
#include "../include/CosExpression.h"
#include "../include/ExponentExpression.h"
#include "../include/LnExpression.h"
#include "../include/LogExpression.h"
#include "../include/MinusExpression.h"
#include "../include/MultiplyExpression.h"
#include "../include/PowerExpression.h"
#include "../include/SinExpression.h"
#include "../include/ValueExpression.h"


DivideExpression::DivideExpression(): left(nullptr), right(nullptr) {}

DivideExpression::DivideExpression(std::unique_ptr<Expression> left,
                                   std::unique_ptr<Expression> right): left(std::move(left)),
                                                                       right(std::move(right)) {}

DivideExpression::DivideExpression(const DivideExpression& other) {
    left = std::move(other.left->clone());
    right = std::move(std::unique_ptr(other.right->clone()));
}

DivideExpression::DivideExpression(DivideExpression&& other) noexcept: left(std::move(other.left)),
                                                                       right(std::move(other.right)) {}

std::string DivideExpression::to_string() const {
    if (left == nullptr || right == nullptr) return "/";
    const auto left_part = part_to_string(left->clone());
    const auto right_part = part_to_string(right->clone());
    if (left_part.empty() || right_part.empty()) return "";
    if (left_part == "0") return "0";
    if (right_part == "1") return "" + left_part;
    return left_part + "/" + right_part;
}

std::string DivideExpression::part_to_string(const std::unique_ptr<Expression>& target) {
    if (const auto* constant_expression = dynamic_cast<ConstantExpression*>(target.get())) {
        const auto str = constant_expression->to_string();
        if (str.empty()) return "";
        if (str == "0") return "0";
        if (str == "1") return "1";
        return std::string(std::string_view(str));
    }
    if (const auto* value_expression = dynamic_cast<ValueExpression*>(target.get())) {
        const auto str = value_expression->to_string();
        if (str.empty()) return "";
        if (str == "0") return "0";
        if (str == "1") return "1";
        return std::string(std::string_view(str));
    }
    if (const auto* sin_expression = dynamic_cast<SinExpression*>(target.get())) {
        const auto str = sin_expression->to_string();
        if (str.empty()) return "";
        if (str == "0") return "0";
        if (str == "1") return "1";
        return std::string(std::string_view(str));
    }
    if (const auto* cos_expression = dynamic_cast<CosExpression*>(target.get())) {
        const auto str = cos_expression->to_string();
        if (str.empty()) return "";
        if (str == "0") return "0";
        if (str == "1") return "1";
        return std::string(std::string_view(str));
    }
    if (const auto* ln_expression = dynamic_cast<LnExpression*>(target.get())) {
        const auto str = ln_expression->to_string();
        if (str.empty()) return "";
        return std::string(std::string_view(str));
    }
    if (const auto* exp_expression = dynamic_cast<ExponentExpression*>(target.get())) {
        const auto str = exp_expression->to_string();
        if (str.empty()) return "";
        if (str == "1") return "1";
        return std::string(std::string_view(str));
    }
    if (const auto* log_expression = dynamic_cast<LogExpression*>(target.get())) {
        const auto str = log_expression->to_string();
        if (str.empty()) return "";
        if (str == "1") return "1";
        return std::string(std::string_view(str));
    }
    if (const auto* power_expression = dynamic_cast<PowerExpression*>(target.get())) {
        const auto str = power_expression->to_string();
        if (str.empty()) return "";
        if (str == "1") return "1";
        return std::string(std::string_view(str));
    }

    const auto str = target->to_string();
    if (str.empty()) return "";
    if (str == "0") return "0";
    if (str == "1") return "1";
    return "(" + str + ")";
}

DivideExpression& DivideExpression::operator=(const DivideExpression& other) {
    left = std::move(other.left->clone());
    right = std::move(std::unique_ptr(other.right->clone()));
    return *this;
}

DivideExpression& DivideExpression::operator=(DivideExpression&& other) noexcept {
    left = std::move(other.left);
    right = std::move(other.right);
    return *this;
}

std::unique_ptr<Expression> DivideExpression::clone() const {
    return std::make_unique<DivideExpression>(*this);
}

double_t DivideExpression::evaluate(const std::map<std::string, double_t> values) const {
    const auto leftResult = left->evaluate(values);
    const auto rightResult = right->evaluate(values);
    return leftResult / rightResult;
}

std::unique_ptr<Expression> DivideExpression::differentiate(const std::string_view variable) const {
    const auto left_result = left->differentiate(variable);
    const auto right_result = right->differentiate(variable);
    const auto left_multiply = MultiplyExpression(left_result->clone(), right->clone());
    const auto right_multiply = MultiplyExpression(left->clone(), right_result->clone());
    const auto denominator = MultiplyExpression(right->clone(), right->clone());
    return std::make_unique<DivideExpression>(
        std::make_unique<MinusExpression>(left_multiply.clone(), right_multiply.clone()),
        denominator.clone()
    );
}

bool DivideExpression::equals(const Expression& other) const {
    const auto& other_casted = dynamic_cast<const DivideExpression&>(other);
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
