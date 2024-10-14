#include <gtest/gtest.h>
#include "Functions/LineFunction.h"

TEST(LineFunctionTests, Value_WithMismatchedSizeOfPoint_ShouldThrowException)
{
    Vector parameters;
    parameters << 1.0, 2.0;

    Functions::LineFunction lineFunction;
    auto function = lineFunction.Bind(parameters);

    Vector point;
    point << 1.0, 2.0, 3.0;

    ASSERT_THROW(function->Value(point), std::runtime_error);
}

TEST(LineFunctionTests, Value_WithZeroSizeOfCoefficients_ShouldReturnFreeMember)
{
    Vector parameters;
    parameters << 1.0;

    Functions::LineFunction lineFunction;
    auto function = lineFunction.Bind(parameters);

    Vector point1;
    point1 << 1.0, 2.0, 3.0;
    auto value1 = function->Value(point1);

    Vector point2;
    auto value2 = function->Value(point2);

    EXPECT_EQ(value1, 1.0);
    EXPECT_EQ(value2, 1.0);
}

TEST(LineFunctionTests, Value_WithCoefficients_ShouldReturnFunctionValue)
{
    Vector parameters;
    parameters << 1.0, 2.0, 3.0;

    Functions::LineFunction lineFunction;
    auto function = lineFunction.Bind(parameters);

    Vector point;
    point << 1.0, 2.0;

    auto value = function->Value(point);

    ASSERT_EQ(value, 1.0 * 1.0 + 2.0 * 2.0 + 3.0);
}

TEST(LineFunctionTests, Gradient_WithCoefficients_ShouldReturnFunctionGradient)
{
    Vector parameters;
    parameters << 1.0, 2.0, 3.0;

    Functions::LineFunction lineFunction;
    auto function = lineFunction.Bind(parameters);

    auto& differentiableFunction = dynamic_cast<Functions::IDifferentiableFunction&>(*function);

    Vector point1;
    point1 << 1.0;

    auto gradient1 = differentiableFunction.Gradient(point1);

    Vector point2;

    auto gradient2 = differentiableFunction.Gradient(point2);

    Vector expectedGradient;
    expectedGradient << 1.0, 2.0;

    EXPECT_EQ(gradient1, expectedGradient);
    EXPECT_EQ(gradient2, expectedGradient);
}

TEST(LineFunctionTests, Gradient_WithZeroSizeOfCoefficients_ShouldReturnFunctionGradient)
{
    Vector parameters;
    parameters << 1.0;

    Functions::LineFunction lineFunction;
    auto function = lineFunction.Bind(parameters);

    auto& differentiableFunction = dynamic_cast<Functions::IDifferentiableFunction&>(*function);

    Vector point1;
    point1 << 1.0;

    auto gradient1 = differentiableFunction.Gradient(point1);

    Vector point2;

    auto gradient2 = differentiableFunction.Gradient(point2);

    Vector expectedGradient;
    expectedGradient << 0.0;

    EXPECT_EQ(gradient1, expectedGradient);
    EXPECT_EQ(gradient2, expectedGradient);
}
