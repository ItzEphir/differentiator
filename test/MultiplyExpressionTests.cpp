//
// Created by ephir on 27.03.2025.
//

#include <gtest/gtest.h>

#include "../include/MultiplyExpression.h"
#include "../include/ConstantExpression.h"
#include "../include/PlusExpression.h"
#include "../include/ValueExpression.h"

struct MultiplyExpressionTests : testing::Test {
    static MultiplyExpression create(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right) {
        auto result = MultiplyExpression();
        result.left = std::move(left);
        result.right = std::move(right);
        return result;
    }
};

TEST_F(MultiplyExpressionTests, CreateEmpty) {
    const auto expected = create(nullptr, nullptr);
    const auto actual = MultiplyExpression();
    ASSERT_EQ(actual, expected);
}

TEST_F(MultiplyExpressionTests, Create) {
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = MultiplyExpression(std::make_unique<ConstantExpression>(12.0),
                                           std::make_unique<ConstantExpression>(11.0));
    ASSERT_EQ(expected, actual);
}

TEST_F(MultiplyExpressionTests, Copy) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = MultiplyExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(MultiplyExpressionTests, Move) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(MultiplyExpressionTests, CopyAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    auto actual = create(std::make_unique<ConstantExpression>(11.0), std::make_unique<ConstantExpression>(11.0));
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(MultiplyExpressionTests, MoveAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    auto actual = create(std::make_unique<ConstantExpression>(11.0), std::make_unique<ConstantExpression>(11.0));
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(MultiplyExpressionTests, Differentiate) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = PlusExpression(
        std::make_unique<MultiplyExpression>(std::make_unique<ConstantExpression>(0.0),
                                             std::make_unique<ConstantExpression>(11.0)),
        std::make_unique<MultiplyExpression>(std::make_unique<ConstantExpression>(12.0),
                                             std::make_unique<ConstantExpression>(0.0)));
    const auto actual = *dynamic_cast<PlusExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(MultiplyExpressionTests, Evaluate) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ValueExpression>("x"));
    constexpr auto expected = 48.0;
    const auto actual = given.evaluate(std::map<std::string, double_t>{
        {"x", 4.0},
    });
    ASSERT_EQ(expected, actual);
}


TEST_F(MultiplyExpressionTests, ToString) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ValueExpression>("x"));
    constexpr auto expected = "12.000000*x";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}
