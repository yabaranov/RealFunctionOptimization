#include <gtest/gtest.h>
#include "Functions/LineFunctionBase.h"

TEST(LineFunctionBaseTests, Constructor_WithEmptyParameters_ShouldThrowException)
{
    Vector parameters;

    ASSERT_THROW(Functions::LineFunctionBase lineFunctionBase(parameters), std::runtime_error);
}

TEST(LineFunctionBaseTests, Constructor_WithOneParameter_ShouldInitFreeMember)
{
    Vector parameters(1);
    parameters << 1.0;

    Functions::LineFunctionBase lineFunctionBase(parameters);

    ASSERT_EQ(lineFunctionBase.GetFreeMember(), 1.0);
}

TEST(LineFunctionBaseTests, Constructor_WithTwoParameters_ShouldInitOneCoefficientAndFreeMember)
{
    Vector parameters(2);
    parameters << 1.0, 2.0;

    Functions::LineFunctionBase lineFunctionBase(parameters);

    ASSERT_EQ(lineFunctionBase.GetCoefficient(0), 1.0);
    ASSERT_EQ(lineFunctionBase.GetFreeMember(), 2.0);
}

TEST(LineFunctionBaseTests, Constructor_WithManyParameters_ShouldInitCoefficientsAndFreeMember)
{
    Vector parameters(3);
    parameters << 1.0, 2.0, 3.0;

    Functions::LineFunctionBase lineFunctionBase(parameters);

    ASSERT_EQ(lineFunctionBase.GetCoefficient(0), 1.0);
    ASSERT_EQ(lineFunctionBase.GetCoefficient(1), 2.0);
    ASSERT_EQ(lineFunctionBase.GetFreeMember(), 3.0);
}
