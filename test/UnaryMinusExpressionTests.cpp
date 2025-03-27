//
// Created by ephir on 27.03.2025.
//

#include <gtest/gtest.h>

#include "../include/UnaryMinusExpression.h"
#include "../include/ConstantExpression.h"
#include "../include/DivideExpression.h"
#include "../include/MultiplyExpression.h"
#include "../include/ValueExpression.h"

struct UnaryMinusExpressionTests : testing::Test {
    static UnaryMinusExpression create(std::unique_ptr<Expression> target) {
        auto result = UnaryMinusExpression();
        result.target = std::move(target);
        return result;
    }
};

TEST_F(UnaryMinusExpressionTests, CreateEmpty) {
    const auto expected = create(nullptr);
    const auto actual = UnaryMinusExpression();
    ASSERT_EQ(actual, expected);
}

TEST_F(UnaryMinusExpressionTests, Create) {
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = UnaryMinusExpression(std::make_unique<ConstantExpression>(2.0));
    ASSERT_EQ(expected, actual);
}

TEST_F(UnaryMinusExpressionTests, Copy) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = UnaryMinusExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(UnaryMinusExpressionTests, Move) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(UnaryMinusExpressionTests, CopyAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    auto actual = create(std::make_unique<ConstantExpression>(3.0));
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(UnaryMinusExpressionTests, MoveAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    auto actual = create(std::make_unique<ConstantExpression>(3.0));
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(UnaryMinusExpressionTests, Differentiate) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0));
    const auto expected = UnaryMinusExpression(std::make_unique<ConstantExpression>(0.0));
    const auto actual = *dynamic_cast<UnaryMinusExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(UnaryMinusExpressionTests, Evaluate) {
    const auto given = create(std::make_unique<ValueExpression>("x"));
    constexpr auto expected = -4.0;
    const auto actual = given.evaluate(std::map<std::string, double_t>{
        {"x", 4.0},
    });
    ASSERT_EQ(expected, actual);
}

TEST_F(UnaryMinusExpressionTests, ToString) {
    const auto given = create(std::make_unique<MultiplyExpression>(
        std::make_unique<ConstantExpression>(2.0),
        std::make_unique<ConstantExpression>(4.0)
    ));
    constexpr auto expected = "-(2.000000*4.000000)";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}
