//
// Created by ephir on 17.03.2025.
//

#include <gtest/gtest.h>

#include "../include/ConstantExpression.h"

struct ConstantExpressionTests : testing::Test {
    static ConstantExpression create(const double_t value) {
        auto result = ConstantExpression();
        result.value = value;
        return result;
    }
};

TEST_F(ConstantExpressionTests, CreateWithDouble) {
    constexpr auto given = 1.2345;
    const auto expected = create(given);
    const auto actual = ConstantExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(ConstantExpressionTests, Copy) {
    const auto given = create(1.2345);
    const auto expected = create(1.2345);
    const auto actual = ConstantExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(ConstantExpressionTests, Move) {
    const auto given = create(1.2345);
    const auto expected = create(1.2345);
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(ConstantExpressionTests, CopyAssignment) {
    const auto given = create(1.2345);
    const auto expected = create(1.2345);
    auto actual = create(222);
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(ConstantExpressionTests, MoveAssignment) {
    const auto given = create(1.2345);
    const auto expected = create(1.2345);
    auto actual = create(222);
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(ConstantExpressionTests, Differentiate) {
    const auto given = create(1.2345);
    const auto expected = create(0);
    const auto actual = *dynamic_cast<ConstantExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(ConstantExpressionTests, Evaluate) {
    const auto given = create(1.2345);
    constexpr auto expected = 1.2345;
    const auto actual = given.evaluate(std::map<std::string, double_t>());
    ASSERT_EQ(expected, actual);
}


TEST_F(ConstantExpressionTests, ToString) {
    const auto given = create(1.2345);
    const auto expected = "1.234500";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}