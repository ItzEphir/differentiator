//
// Created by ephir on 27.03.2025.
//

#include <gtest/gtest.h>

#include "../include/LnExpression.h"
#include "../include/ConstantExpression.h"
#include "../include/DivideExpression.h"
#include "../include/ValueExpression.h"

struct LnExpressionTests : testing::Test {
    static LnExpression create(std::unique_ptr<Expression> target) {
        auto result = LnExpression();
        result.target = std::move(target);
        return result;
    }
};

TEST_F(LnExpressionTests, CreateEmpty) {
    const auto expected = create(nullptr);
    const auto actual = LnExpression();
    ASSERT_EQ(actual, expected);
}

TEST_F(LnExpressionTests, Create) {
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = LnExpression(std::make_unique<ConstantExpression>(2.0));
    ASSERT_EQ(expected, actual);
}

TEST_F(LnExpressionTests, Copy) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = LnExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(LnExpressionTests, Move) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(LnExpressionTests, CopyAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    auto actual = create(std::make_unique<ConstantExpression>(3.0));
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(LnExpressionTests, MoveAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    auto actual = create(std::make_unique<ConstantExpression>(3.0));
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(LnExpressionTests, Differentiate) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0));
    const auto expected = DivideExpression(
        std::make_unique<ConstantExpression>(0.0),
        std::make_unique<ConstantExpression>(12.0)
    );
    const auto actual = *dynamic_cast<DivideExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(LnExpressionTests, Evaluate) {
    const auto given = create(std::make_unique<ValueExpression>("x"));
    const auto expected = log(4.0);
    const auto actual = given.evaluate(std::map<std::string, double_t>{
        {"x", 4.0},
    });
    ASSERT_EQ(expected, actual);
}


TEST_F(LnExpressionTests, ToString) {
    const auto given = create(std::make_unique<ValueExpression>("x"));
    const auto expected = "ln(x)";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}
