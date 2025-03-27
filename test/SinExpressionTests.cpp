//
// Created by ephir on 27.03.2025.
//

#include <gtest/gtest.h>

#include "../include/SinExpression.h"
#include "../include/ConstantExpression.h"
#include "../include/CosExpression.h"
#include "../include/MultiplyExpression.h"
#include "../include/ValueExpression.h"

struct SinExpressionTests : testing::Test {
    static SinExpression create(std::unique_ptr<Expression> target) {
        auto result = SinExpression();
        result.target = std::move(target);
        return result;
    }
};

TEST_F(SinExpressionTests, CreateEmpty) {
    const auto expected = create(nullptr);
    const auto actual = SinExpression();
    ASSERT_EQ(actual, expected);
}

TEST_F(SinExpressionTests, Create) {
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = SinExpression(std::make_unique<ConstantExpression>(2.0));
    ASSERT_EQ(expected, actual);
}

TEST_F(SinExpressionTests, Copy) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = SinExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(SinExpressionTests, Move) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(SinExpressionTests, CopyAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    auto actual = create(std::make_unique<ConstantExpression>(3.0));
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(SinExpressionTests, MoveAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    auto actual = create(std::make_unique<ConstantExpression>(3.0));
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(SinExpressionTests, Differentiate) {
    const auto given = create(std::make_unique<ConstantExpression>(0.5));
    const auto expected = MultiplyExpression(
        std::make_unique<ConstantExpression>(0.0),
        std::make_unique<CosExpression>(std::make_unique<ConstantExpression>(0.5))
    );
    const auto actual = *dynamic_cast<MultiplyExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(SinExpressionTests, Evaluate) {
    const auto given = create(std::make_unique<ValueExpression>("x"));
    const auto expected = sin(4.0);
    const auto actual = given.evaluate(std::map<std::string, double_t>{
        {"x", 4.0},
    });
    ASSERT_EQ(expected, actual);
}

TEST_F(SinExpressionTests, ToString) {
    const auto given = create(std::make_unique<ValueExpression>("x"));
    const auto expected = "sin(x)";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}
