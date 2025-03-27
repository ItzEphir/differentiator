//
// Created by ephir on 27.03.2025.
//

#include <gtest/gtest.h>

#include "../include/CosExpression.h"
#include "../include/ConstantExpression.h"
#include "../include/MultiplyExpression.h"
#include "../include/SinExpression.h"
#include "../include/UnaryMinusExpression.h"
#include "../include/ValueExpression.h"

struct CosExpressionTests : testing::Test {
    static CosExpression create(std::unique_ptr<Expression> target) {
        auto result = CosExpression();
        result.target = std::move(target);
        return result;
    }
};

TEST_F(CosExpressionTests, CreateEmpty) {
    const auto expected = create(nullptr);
    const auto actual = CosExpression();
    ASSERT_EQ(actual, expected);
}

TEST_F(CosExpressionTests, Create) {
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = CosExpression(std::make_unique<ConstantExpression>(2.0));
    ASSERT_EQ(expected, actual);
}

TEST_F(CosExpressionTests, Copy) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = CosExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(CosExpressionTests, Move) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(CosExpressionTests, CopyAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    auto actual = create(std::make_unique<ConstantExpression>(3.0));
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(CosExpressionTests, MoveAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(2.0));
    const auto expected = create(std::make_unique<ConstantExpression>(2.0));
    auto actual = create(std::make_unique<ConstantExpression>(3.0));
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(CosExpressionTests, Differentiate) {
    const auto given = create(std::make_unique<ConstantExpression>(0.5));
    const auto expected = MultiplyExpression(
        std::make_unique<ConstantExpression>(0.0),
        std::make_unique<UnaryMinusExpression>(
            std::make_unique<SinExpression>(std::make_unique<ConstantExpression>(0.5))
        )
    );
    const auto actual = *dynamic_cast<MultiplyExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(CosExpressionTests, Evaluate) {
    const auto given = create(std::make_unique<ValueExpression>("x"));
    const auto expected = cos(4.0);
    const auto actual = given.evaluate(std::map<std::string, double_t>{
        {"x", 4.0},
    });
    ASSERT_EQ(expected, actual);
}

TEST_F(CosExpressionTests, ToString) {
    const auto given = create(std::make_unique<ValueExpression>("x"));
    const auto expected = "cos(x)";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}
