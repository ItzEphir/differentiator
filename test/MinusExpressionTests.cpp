//
// Created by ephir on 27.03.2025.
//

#include <gtest/gtest.h>

#include "../include/ConstantExpression.h"
#include "../include/MinusExpression.h"
#include "../include/ValueExpression.h"

struct MinusExpressionTests : testing::Test {
    static MinusExpression create(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right) {
        auto result = MinusExpression();
        result.left = std::move(left);
        result.right = std::move(right);
        return result;
    }
};

TEST_F(MinusExpressionTests, CreateEmpty) {
    const auto expected = create(nullptr, nullptr);
    const auto actual = MinusExpression();
    ASSERT_EQ(actual, expected);
}

TEST_F(MinusExpressionTests, Create) {
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = MinusExpression(std::make_unique<ConstantExpression>(12.0),
                                       std::make_unique<ConstantExpression>(11.0));
    ASSERT_EQ(expected, actual);
}

TEST_F(MinusExpressionTests, Copy) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = MinusExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(MinusExpressionTests, Move) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(MinusExpressionTests, CopyAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    auto actual = create(std::make_unique<ConstantExpression>(11.0), std::make_unique<ConstantExpression>(11.0));
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(MinusExpressionTests, MoveAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    auto actual = create(std::make_unique<ConstantExpression>(11.0), std::make_unique<ConstantExpression>(11.0));
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(MinusExpressionTests, Differentiate) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(0.0), std::make_unique<ConstantExpression>(0.0));
    const auto actual = *dynamic_cast<MinusExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(MinusExpressionTests, Evaluate) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ValueExpression>("x"));
    constexpr auto expected = 8.0;
    const auto actual = given.evaluate(std::map<std::string, double_t>{
        {"x", 4.0},
    });
    ASSERT_EQ(expected, actual);
}

TEST_F(MinusExpressionTests, ToString) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ValueExpression>("x"));
    constexpr auto expected = "12.000000-x";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}
