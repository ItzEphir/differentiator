//
// Created by ephir on 27.03.2025.
//

#include <gtest/gtest.h>

#include "../include/ConstantExpression.h"
#include "../include/PlusExpression.h"
#include "../include/ValueExpression.h"

struct PlusExpressionTests : testing::Test {
    static PlusExpression create(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right) {
        auto result = PlusExpression();
        result.left = std::move(left);
        result.right = std::move(right);
        return result;
    }
};

TEST_F(PlusExpressionTests, CreateEmpty) {
    const auto expected = create(nullptr, nullptr);
    const auto actual = PlusExpression();
    ASSERT_EQ(actual, expected);
}

TEST_F(PlusExpressionTests, Create) {
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = PlusExpression(std::make_unique<ConstantExpression>(12.0),
                                       std::make_unique<ConstantExpression>(11.0));
    ASSERT_EQ(expected, actual);
}

TEST_F(PlusExpressionTests, Copy) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = PlusExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(PlusExpressionTests, Move) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(PlusExpressionTests, CopyAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    auto actual = create(std::make_unique<ConstantExpression>(11.0), std::make_unique<ConstantExpression>(11.0));
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(PlusExpressionTests, MoveAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    auto actual = create(std::make_unique<ConstantExpression>(11.0), std::make_unique<ConstantExpression>(11.0));
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(PlusExpressionTests, Differentiate) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(0.0), std::make_unique<ConstantExpression>(0.0));
    const auto actual = *dynamic_cast<PlusExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(PlusExpressionTests, Evaluate) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ValueExpression>("x"));
    constexpr auto expected = 16.0;
    const auto actual = given.evaluate(std::map<std::string, double_t>{
        {"x", 4.0},
    });
    ASSERT_EQ(expected, actual);
}

TEST_F(PlusExpressionTests, ToString) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ValueExpression>("x"));
    constexpr auto expected = "12.000000+x";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}
