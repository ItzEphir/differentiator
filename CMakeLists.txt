cmake_minimum_required(VERSION 3.25)
project(differentiator)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(tests test.cpp
        include/Expression.h
        src/ConstantExpression.cpp
        include/ConstantExpression.h
        src/ValueExpression.cpp
        include/ValueExpression.h
        test/ConstantExpressionTests.cpp
        test/ValueExpressionTests.cpp
        include/PlusExpression.h
        src/PlusExpression.cpp
        test/PlusExpressionTests.cpp
        include/MinusExpression.h
        src/MinusExpression.cpp
        test/MinusExpressionTests.cpp
        include/MultiplyExpression.h
        src/MultiplyExpression.cpp
        test/MultiplyExpressionTests.cpp
        include/DivideExpression.h
        src/DivideExpression.cpp
        include/PowerExpression.h
        src/PowerExpression.cpp
        include/ExponentExpression.h
        src/ExponentExpression.cpp
        test/DivideExpressionTests.cpp
        test/PowerExpressionTests.cpp
        test/ExponentExpressionTests.cpp
        include/LnExpression.h
        src/LnExpression.cpp
        include/LogExpression.h
        test/LnExpressionTests.cpp
        src/LogExpression.cpp
        test/LogExpressionTests.cpp
        include/SinExpression.h
        src/SinExpression.cpp
        include/CosExpression.h
        src/CosExpression.cpp
        include/UnaryMinusExpression.h
        src/UnaryMinusExpression.cpp
        test/UnaryMinusExpressionTests.cpp
        test/SinExpressionTests.cpp
        test/CosExpressionTests.cpp
        test/Integration.cpp
        include/Parser.h
        src/Parser.cpp
)

target_link_libraries(tests GTest::gtest GTest::gtest_main)

add_test(NAME Tests COMMAND tests)

add_executable(differentiator main.cpp
        include/Expression.h
        src/ConstantExpression.cpp
        include/ConstantExpression.h
        src/ValueExpression.cpp
        include/ValueExpression.h
        include/PlusExpression.h
        src/PlusExpression.cpp
        include/MinusExpression.h
        src/MinusExpression.cpp
        include/MultiplyExpression.h
        src/MultiplyExpression.cpp
        include/DivideExpression.h
        src/DivideExpression.cpp
        include/PowerExpression.h
        src/PowerExpression.cpp
        include/ExponentExpression.h
        src/ExponentExpression.cpp
        include/LnExpression.h
        src/LnExpression.cpp
        include/LogExpression.h
        src/LogExpression.cpp
        include/SinExpression.h
        src/SinExpression.cpp
        include/CosExpression.h
        src/CosExpression.cpp
        include/UnaryMinusExpression.h
        src/UnaryMinusExpression.cpp
        include/Parser.h
        src/Parser.cpp)
