//
// Created by ephir on 27.03.2025.
//

#include <gtest/gtest.h>

#include "../include/LogExpression.h"
#include "../include/ConstantExpression.h"
#include "../include/DivideExpression.h"
#include "../include/LnExpression.h"
#include "../include/MinusExpression.h"
#include "../include/MultiplyExpression.h"
#include "../include/ValueExpression.h"

struct LogExpressionTests : testing::Test {
    static LogExpression create(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right) {
        auto result = LogExpression();
        result.left = std::move(left);
        result.right = std::move(right);
        return result;
    }
};

TEST_F(LogExpressionTests, CreateEmpty) {
    const auto expected = create(nullptr, nullptr);
    const auto actual = LogExpression();
    ASSERT_EQ(actual, expected);
}

TEST_F(LogExpressionTests, Create) {
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = LogExpression(std::make_unique<ConstantExpression>(12.0),
                                      std::make_unique<ConstantExpression>(11.0));
    ASSERT_EQ(expected, actual);
}

TEST_F(LogExpressionTests, Copy) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = LogExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(LogExpressionTests, Move) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(LogExpressionTests, CopyAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    auto actual = create(std::make_unique<ConstantExpression>(11.0), std::make_unique<ConstantExpression>(11.0));
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(LogExpressionTests, MoveAssignment) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = create(std::make_unique<ConstantExpression>(12.0),
                                 std::make_unique<ConstantExpression>(11.0));
    auto actual = create(std::make_unique<ConstantExpression>(11.0), std::make_unique<ConstantExpression>(11.0));
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(LogExpressionTests, Differentiate) {
    const auto given = create(std::make_unique<ConstantExpression>(12.0), std::make_unique<ConstantExpression>(11.0));
    const auto expected = DivideExpression(
        std::make_unique<MinusExpression>(
            std::make_unique<MultiplyExpression>(
                std::make_unique<DivideExpression>(
                    std::make_unique<ConstantExpression>(0.0),
                    std::make_unique<ConstantExpression>(11.0)
                ),
                std::make_unique<LnExpression>(std::make_unique<ConstantExpression>(12.0))),
            std::make_unique<MultiplyExpression>(
                std::make_unique<LnExpression>(std::make_unique<ConstantExpression>(11.0)),
                std::make_unique<DivideExpression>(
                    std::make_unique<ConstantExpression>(0.0),
                    std::make_unique<ConstantExpression>(12.0)
                )
            )
        ),
        std::make_unique<MultiplyExpression>(
            std::make_unique<LnExpression>(std::make_unique<ConstantExpression>(12.0)),
            std::make_unique<LnExpression>(std::make_unique<ConstantExpression>(12.0))
        )
    );
    const auto actual = *dynamic_cast<DivideExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(LogExpressionTests, Evaluate) {
    const auto given = create(std::make_unique<ConstantExpression>(3), std::make_unique<ValueExpression>("x"));
    const auto expected = log(4) / log(3);
    const auto actual = given.evaluate(std::map<std::string, double_t>{
        {"x", 4.0},
    });
    ASSERT_EQ(expected, actual);
}

TEST_F(LogExpressionTests, ToString) {
    const auto given = create(std::make_unique<ConstantExpression>(3), std::make_unique<ValueExpression>("x"));
    const auto expected = "log(3.000000,x)";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}
