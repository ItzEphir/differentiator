//
// Created by ephir on 17.03.2025.
//

#include <gtest/gtest.h>

#include "../include/ConstantExpression.h"
#include "../include/ValueExpression.h"

using std::string_view_literals::operator ""sv;

struct ValueExpressionTests : testing::Test {
    static ValueExpression create(const std::string_view name) {
        auto result = ValueExpression();
        result.name = name;
        return result;
    }
};

TEST_F(ValueExpressionTests, CreateWithStringView) {
    constexpr auto given = "x"sv;
    const auto expected = create(given);
    const auto actual = ValueExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(ValueExpressionTests, Copy) {
    const auto given = create("x");
    const auto expected = create("x");
    const auto actual = ValueExpression(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(ValueExpressionTests, Move) {
    const auto given = create("x");
    const auto expected = create("x");
    const auto actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(ValueExpressionTests, CopyAssignment) {
    const auto given = create("x");
    const auto expected = create("x");
    auto actual = create("y");
    actual = given;
    ASSERT_EQ(expected, actual);
}

TEST_F(ValueExpressionTests, MoveAssignment) {
    const auto given = create("x");
    const auto expected = create("x");
    auto actual = create("y");
    actual = std::move(given);
    ASSERT_EQ(expected, actual);
}

TEST_F(ValueExpressionTests, DifferentiateBySameName) {
    const auto given = create("x");
    const auto expected = ConstantExpression(1);
    const auto actual = *dynamic_cast<ConstantExpression*>(given.differentiate("x").get());
    ASSERT_EQ(expected, actual);
}

TEST_F(ValueExpressionTests, ToString) {
    const auto given = create("x");
    const auto expected = "x";
    const auto actual = given.to_string();
    ASSERT_EQ(expected, actual);
}
