#include <gtest/gtest.h>
#include "Functions/Factories/LineFunctionFactory.h"

TEST(LineFunctionTests, Value_WithCoefficientsAndSizeOfPointMismatchNumberOfCoefficients_ShouldThrowException)
{
    Vector parameters(3);
    parameters << 1.0, 2.0, 3.0;

    auto function = Functions::LineFunctionFactory().CreateFunction(parameters);

    Vector point(3);
    point << 1.0, 2.0, 3.0;

    ASSERT_THROW(function->Value(point), std::runtime_error);
}

TEST(LineFunctionTests, Value_WithEmptyCoefficients_ShouldReturnFreeMemberRegardlessOfPoint)
{
    Vector parameters(1);
    parameters << 1.0;

    auto function = Functions::LineFunctionFactory().CreateFunction(parameters);

    Vector point1(3);
    point1 << 1.0, 2.0, 3.0;
    auto value1 = function->Value(point1);

    Vector point2;
    auto value2 = function->Value(point2);

    EXPECT_EQ(value1, 1.0);
    EXPECT_EQ(value2, 1.0);
}

TEST(LineFunctionTests, Value_WithCoefficients_ShouldReturnFunctionValue)
{
    Vector parameters(3);
    parameters << 1.0, 2.0, 3.0;

    auto function = Functions::LineFunctionFactory().CreateFunction(parameters);

    Vector point(2);
    point << 1.0, 2.0;

    auto value = function->Value(point);

    ASSERT_EQ(value, 1.0 * 1.0 + 2.0 * 2.0 + 3.0);
}

TEST(LineFunctionTests, Gradient_WithCoefficients_ShouldReturnGradientRegardlessOfPoint)
{
    Vector parameters(3);
    parameters << 1.0, 2.0, 3.0;

    auto function = Functions::LineFunctionFactory().CreateFunction(parameters);

    auto& differentiableFunction = dynamic_cast<Functions::IDifferentiableFunction&>(*function);

    Vector point1(3);
    point1 << 1.0, 2.0, 3.0;
    auto gradient1 = differentiableFunction.Gradient(point1);

    Vector point2;
    auto gradient2 = differentiableFunction.Gradient(point2);

    Vector expectedGradient(3);
    expectedGradient << 1.0, 2.0, 1.0;

    EXPECT_EQ(gradient1, expectedGradient);
    EXPECT_EQ(gradient2, expectedGradient);
}

TEST(LineFunctionTests, Gradient_WithEmptyCoefficients_ShouldReturnOneRegardlessOfPoint)
{
    Vector parameters(1);
    parameters << 1.0;

    auto function = Functions::LineFunctionFactory().CreateFunction(parameters);

    auto& differentiableFunction = dynamic_cast<Functions::IDifferentiableFunction&>(*function);

    Vector point1(3);
    point1 << 1.0, 2.0, 3.0;
    auto gradient1 = differentiableFunction.Gradient(point1);

    Vector point2;
    auto gradient2 = differentiableFunction.Gradient(point2);

    Vector expectedGradient(1);
    expectedGradient << 1.0;

    EXPECT_EQ(gradient1, expectedGradient);
    EXPECT_EQ(gradient2, expectedGradient);
}
