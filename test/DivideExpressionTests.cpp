//
// Created by ephir on 27.03.2025.
//

#include <gtest/gtest.h>

#include "../include/DivideExpression.h"
#include "../include/ConstantExpression.h"
#include "../include/MinusExpression.h"
#include "../include/MultiplyExpression.h"
#include "../include/ValueExpression.h"

struct DivideExpressionTests : testing::Test {
    static DivideExpression create(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right) {
        auto result = DivideExpression();
        result.left = std::move(left);
        result.right = std::move(right);
        return result;
    }
};

TEST_F(DivideExpressionTests, CreateEmpty) {
    const auto expected = create(nullptr, nullptr);
    const auto actual = DivideExpression();
    ASSERT_EQ(actual, expected);
}

TEST_F(DivideExpressionTests, Create) {
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = DivideExpression(std::make_unique<ConstantExpression>(12.0),
                                         std::make_unique<ConstantExpression>(11.0));
    ASSERT_EQ(expected, actual);
}

TEST_F(DivideExpressionTests, Copy) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = DivideExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(DivideExpressionTests, Move) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(DivideExpressionTests, CopyAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    auto actual = create(std::make_unique<ConstantExpression>(11.0), std::make_unique<ConstantExpression>(11.0));
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(DivideExpressionTests, MoveAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    auto actual = create(std::make_unique<ConstantExpression>(11.0), std::make_unique<ConstantExpression>(11.0));
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(DivideExpressionTests, Differentiate) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = DivideExpression(
        std::make_unique<MinusExpression>(
            std::make_unique<MultiplyExpression>(std::make_unique<ConstantExpression>(0.0),
                                                 std::make_unique<ConstantExpression>(11.0)),
            std::make_unique<MultiplyExpression>(std::make_unique<ConstantExpression>(12.0),
                                                 std::make_unique<ConstantExpression>(0.0))
        ),
        std::make_unique<MultiplyExpression>(std::make_unique<ConstantExpression>(11.0),
                                             std::make_unique<ConstantExpression>(11.0))
    );
    const auto actual = *dynamic_cast<DivideExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(DivideExpressionTests, Evaluate) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ValueExpression>("x"));
    constexpr auto expected = 3.0;
    const auto actual = given.evaluate(std::map<std::string, double_t>{
        {"x", 4.0},
    });
    ASSERT_EQ(expected, actual);
}

TEST_F(DivideExpressionTests, ToString) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ValueExpression>("x"));
    const auto expected = "12.000000/x";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}
