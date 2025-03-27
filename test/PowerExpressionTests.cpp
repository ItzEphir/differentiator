//
// Created by ephir on 27.03.2025.
//

#include <gtest/gtest.h>

#include "../include/PowerExpression.h"
#include "../include/ConstantExpression.h"
#include "../include/DivideExpression.h"
#include "../include/LnExpression.h"
#include "../include/MultiplyExpression.h"
#include "../include/PlusExpression.h"
#include "../include/ValueExpression.h"

struct PowerExpressionTests : testing::Test {
    static PowerExpression create(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right) {
        auto result = PowerExpression();
        result.left = std::move(left);
        result.right = std::move(right);
        return result;
    }
};

TEST_F(PowerExpressionTests, CreateEmpty) {
    const auto expected = create(nullptr, nullptr);
    const auto actual = PowerExpression();
    ASSERT_EQ(actual, expected);
}

TEST_F(PowerExpressionTests, Create) {
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = PowerExpression(std::make_unique<ConstantExpression>(12.0),
                                        std::make_unique<ConstantExpression>(11.0));
    ASSERT_EQ(expected, actual);
}

TEST_F(PowerExpressionTests, Copy) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = PowerExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(PowerExpressionTests, Move) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(PowerExpressionTests, CopyAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    auto actual = create(std::make_unique<ConstantExpression>(11.0), std::make_unique<ConstantExpression>(11.0));
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(PowerExpressionTests, MoveAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    auto actual = create(std::make_unique<ConstantExpression>(11.0), std::make_unique<ConstantExpression>(11.0));
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(PowerExpressionTests, Differentiate) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = MultiplyExpression(
        std::make_unique<PlusExpression>(
            std::make_unique<MultiplyExpression>(
                std::make_unique<ConstantExpression>(0.0),
                std::make_unique<LnExpression>(
                    std::make_unique<ConstantExpression>(12.0))),
            std::make_unique<MultiplyExpression>(
                std::make_unique<ConstantExpression>(11.0),
                std::make_unique<DivideExpression>(
                    std::make_unique<ConstantExpression>(0.0),
                    std::make_unique<ConstantExpression>(12.0)
                )
            )
        ),
        std::make_unique<PowerExpression>(
            std::make_unique<ConstantExpression>(12.0),
            std::make_unique<ConstantExpression>(11.0)
        )
    );
    const auto actual = *dynamic_cast<MultiplyExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(PowerExpressionTests, Evaluate) {
    const auto given = create(std::make_unique<ConstantExpression>(3), std::make_unique<ValueExpression>("x"));
    constexpr auto expected = 81.0;
    const auto actual = given.evaluate(std::map<std::string, double_t>{
        {"x", 4.0},
    });
    ASSERT_EQ(expected, actual);
}

TEST_F(PowerExpressionTests, ToString) {
    const auto given = create(std::make_unique<ConstantExpression>(3), std::make_unique<ValueExpression>("x"));
    constexpr auto expected = "3.000000^x";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}
