#include <gtest/gtest.h>
#include "Functions/InterpolationSplineBase.h"

TEST(InterpolationSplineBaseTests, Constructor_WithEmptyParameters_ShouldThrowException)
{
    Vector parameters;

    ASSERT_THROW(Functions::InterpolationSplineBase interpolationSplineBase(parameters), std::runtime_error);
}

TEST(InterpolationSplineBaseTests, Constructor_WithOddSizeofParameters_ShouldThrowException)
{
    Vector parameters(5);
    parameters << 1.0, 2.0, 2.0, 4.0, 3.0;

    ASSERT_THROW(Functions::InterpolationSplineBase interpolationSplineBase(parameters), std::runtime_error);
}

TEST(InterpolationSplineBaseTests, Constructor_WithTwoParameters_ShouldThrowException)
{
    Vector parameters(2);
    parameters << 1.0, 2.0;

    ASSERT_THROW(Functions::InterpolationSplineBase interpolationSplineBase(parameters), std::runtime_error);
}

TEST(InterpolationSplineBaseTests, Constructor_WithFourParameters_ShouldInitTwoArgumentsAndTwoValues)
{
    Vector parameters(4);
    parameters << 1.0, 2.0, 2.0, 4.0;

    Functions::InterpolationSplineBase interpolationSplineBase(parameters);

    EXPECT_EQ(1.0, interpolationSplineBase.GetArgument(0));
    EXPECT_EQ(2.0, interpolationSplineBase.GetValue(0));
    EXPECT_EQ(2.0, interpolationSplineBase.GetArgument(1));
    EXPECT_EQ(4.0, interpolationSplineBase.GetValue(1));
}

TEST(InterpolationSplineBaseTests, FindIntervalOfArgument_WithSplineHavingManyPointsAndArgumentOutsideSplineDomain_ShouldThrowException)
{
    Vector parameters(6);
    parameters << 1.0, 2.0, 2.0, 4.0, 3.0, 8.0;

    auto argument = 0.0;

    Functions::InterpolationSplineBase interpolationSplineBase(parameters);

    ASSERT_THROW(interpolationSplineBase.FindIntervalOfArgument(argument), std::runtime_error);
}

TEST(InterpolationSplineBaseTests, FindIntervalOfArgument_WithSplineHavingManyPointsAndArgumentInsideSplineDomain_ShouldReturnInterval)
{
    Vector parameters(6);
    parameters << 1.0, 2.0, 2.0, 4.0, 3.0, 8.0;

    auto argument = 1.5;

    Functions::InterpolationSplineBase interpolationSplineBase(parameters);

    auto&& [index1, index2] = interpolationSplineBase.FindIntervalOfArgument(argument);

    EXPECT_EQ(index1, 0);
    EXPECT_EQ(index2, 1);
}
