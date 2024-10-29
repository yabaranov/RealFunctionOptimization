#include <gtest/gtest.h>
#include "Functions/PolynomialFunction.h"

TEST(PolynomialFunctionTests, Bind_WithValidParameters_ShouldReturnUniquePtrToIFunctionAndCastToLineFunctionBase)
{
    Vector parameters(3);
    parameters << 1.0, 2.0, 3.0;

    Functions::PolynomialFunction polynomialFunction;
    std::unique_ptr<Functions::IFunction> function = polynomialFunction.Bind(parameters);

    ASSERT_TRUE(function != nullptr);

    auto lineFunctionBase = dynamic_cast<Functions::LineFunctionBase*>(function.get());

    ASSERT_TRUE(lineFunctionBase != nullptr);
}

TEST(InternalPolynomialFunctionTests, Value_WithCoefficientsAndSizeOfPointNotEqualOne_ShouldThrowException)
{
    Vector parameters(3);
    parameters << 1.0, 2.0, 3.0;

    Functions::PolynomialFunction polynomialFunction;
    auto function = polynomialFunction.Bind(parameters);

    Vector point(3);
    point << 1.0, 2.0, 3.0;

    ASSERT_THROW(function->Value(point), std::runtime_error);
}

TEST(InternalPolynomialFunctionTests, Value_WithCoefficientsAndSizeOfPointEqualOne_ShouldReturnValue)
{
    Vector parameters(3);
    parameters << 1.0, 0.0, 0.0;

    Functions::PolynomialFunction polynomialFunction;
    auto function = polynomialFunction.Bind(parameters);

    Vector point(1);
    point << 3.0;

    auto value = function->Value(point);

    ASSERT_EQ(value, 9.0);
}

TEST(InternalPolynomialFunctionTests, Value_WithEmptyCoefficients_ShouldReturnFreeMemberRegardlessOfPoint)
{
    Vector parameters(1);
    parameters << 1.0;

    Functions::PolynomialFunction polynomialFunction;
    auto function = polynomialFunction.Bind(parameters);

    Vector point1(3);
    point1 << 1.0, 2.0, 3.0;
    auto value1 = function->Value(point1);

    Vector point2;
    auto value2 = function->Value(point2);

    EXPECT_EQ(value1, 1.0);
    EXPECT_EQ(value2, 1.0);
}
