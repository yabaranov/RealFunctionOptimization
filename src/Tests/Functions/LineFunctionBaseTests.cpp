#include <gtest/gtest.h>
#include "Functions/LineFunctionBase.h"

TEST(LineFunctionBaseTests, Constructor_WithEmptyParameters_ShouldThrowException)
{
    Vector parameters;

    ASSERT_THROW(Functions::LineFunctionBase lineFunctionBase(parameters), std::runtime_error);
}

TEST(LineFunctionBaseTests, Constructor_WithOneParameter_ShouldInitFreeMember)
{
    Vector parameters;
    parameters << 1.0;

    Functions::LineFunctionBase lineFunctionBase(parameters);

    ASSERT_EQ(lineFunctionBase.getFreeMember(), 1.0);
}

TEST(LineFunctionBaseTests, Constructor_WithTwoParameters_ShouldInitOneCoefficientAndFreeMember)
{
    Vector parameters;
    parameters << 1.0, 2.0;

    Functions::LineFunctionBase lineFunctionBase(parameters);

    ASSERT_EQ(lineFunctionBase.getCoefficient(0), 1.0);
    ASSERT_EQ(lineFunctionBase.getFreeMember(), 2.0);
}

TEST(LineFunctionBaseTests, Constructor_WithManyParameters_ShouldInitCoefficientsAndFreeMember)
{
    Vector parameters;
    parameters << 1.0, 2.0, 3.0;

    Functions::LineFunctionBase lineFunctionBase(parameters);

    ASSERT_EQ(lineFunctionBase.getCoefficient(0), 1.0);
    ASSERT_EQ(lineFunctionBase.getCoefficient(1), 2.0);
    ASSERT_EQ(lineFunctionBase.getFreeMember(), 3.0);
}
