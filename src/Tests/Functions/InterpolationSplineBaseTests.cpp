#include <gtest/gtest.h>
#include "Functions/InterpolationSplineBase.h"

TEST(InterpolationSplineBaseTests, Constructor_WithEmptyParameters_ShouldThrowException)
{
    Vector parameters;

    ASSERT_THROW(Functions::InterpolationSplineBase interpolationSplineBase(parameters), std::runtime_error);
}

TEST(InterpolationSplineBaseTests, Constructor_WithOddSizeofParameters_ShouldThrowException)
{
    Vector parameters(1);
    parameters << 1.0;

    ASSERT_THROW(Functions::InterpolationSplineBase interpolationSplineBase(parameters), std::runtime_error);
}

TEST(InterpolationSplineBaseTests, Constructor_WithTwoParameters_ShouldThrowException)
{
    Vector parameters(2);
    parameters << 1.0, 2.0;

    Functions::InterpolationSplineBase interpolationSplineBase(parameters);

    ASSERT_THROW(Functions::InterpolationSplineBase interpolationSplineBase(parameters), std::runtime_error);
}

TEST(InterpolationSplineBaseTests, FindIntervalOfArguments_WithSplineHavingManyPointsAndArgumentOutsideSplineDomain_ShouldThrowException)
{
    Vector parameters(6);
    parameters << 1.0, 2.0, 2.0, 4.0, 3.0, 8.0;

    auto argument = 0.0;

    Functions::InterpolationSplineBase interpolationSplineBase(parameters);

    ASSERT_THROW(interpolationSplineBase.FindIntervalOfArguments(argument), std::runtime_error);
}

TEST(InterpolationSplineBaseTests, FindIntervalOfArguments_WithSplineHavingManyPointsAndArgumentInsideSplineDomain_ShouldReturnInterval)
{
    Vector parameters(6);
    parameters << 1.0, 2.0, 2.0, 4.0, 3.0, 8.0;

    auto argument = 0.5;

    Functions::InterpolationSplineBase interpolationSplineBase(parameters);

    auto&& [index1, index2] = interpolationSplineBase.FindIntervalOfArguments(argument);

    EXPECT_EQ(index1, 0);
    EXPECT_EQ(index2, 1);
}
