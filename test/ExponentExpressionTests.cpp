//
// Created by ephir on 27.03.2025.
//

#include <gtest/gtest.h>

#include "../include/ExponentExpression.h"
#include "../include/ConstantExpression.h"
#include "../include/MultiplyExpression.h"
#include "../include/ValueExpression.h"

struct ExponentExpressionTests : testing::Test {
    static ExponentExpression create(std::unique_ptr<Expression> target) {
        auto result = ExponentExpression();
        result.target = std::move(target);
        return result;
    }
};

TEST_F(ExponentExpressionTests, CreateEmpty) {
    const auto expected = create(nullptr);
    const auto actual = ExponentExpression();
    ASSERT_EQ(actual, expected);
}

TEST_F(ExponentExpressionTests, Create) {
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = ExponentExpression(std::make_unique<ConstantExpression>(2.0));
    ASSERT_EQ(expected, actual);
}

TEST_F(ExponentExpressionTests, Copy) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = ExponentExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(ExponentExpressionTests, Move) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(ExponentExpressionTests, CopyAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    auto actual = create(std::make_unique<ConstantExpression>(3.0));
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(ExponentExpressionTests, MoveAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    auto actual = create(std::make_unique<ConstantExpression>(3.0));
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(ExponentExpressionTests, Differentiate) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = MultiplyExpression(
        std::make_unique<ConstantExpression>(0.0),
        std::make_unique<ExponentExpression>(std::make_unique<ConstantExpression>(2.0))
    );
    const auto actual = *dynamic_cast<MultiplyExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(ExponentExpressionTests, Evaluate) {
    const auto given = create(std::make_unique<ValueExpression>("x"));
    const auto expected = exp(4.0);
    const auto actual = given.evaluate(std::map<std::string, double_t>{
        {"x", 4.0},
    });
    ASSERT_EQ(expected, actual);
}

TEST_F(ExponentExpressionTests, ToString) {
    const auto given = create(std::make_unique<ValueExpression>("x"));
    const auto expected = "exp(x)";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}
