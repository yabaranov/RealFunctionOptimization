#include <gtest/gtest.h>
#include "Functions/SplineBase.h"

TEST(SplineBaseTests, Constructor_WithNoParametersOrArguments_ShouldThrowException)
{
    Vector parameters;

    ASSERT_THROW(Functions::SplineBase interpolationSplineBase(parameters, parameters), std::runtime_error);
}

TEST(SplineBaseTests, Constructor_WithNonMatchingParametersAndArguments_ShouldThrowException)
{
    Vector parameters(2);
    Vector arguments(1);

    ASSERT_THROW(Functions::SplineBase interpolationSplineBase(arguments, parameters), std::runtime_error);
}

TEST(SplineBaseTests, Constructor_WithSingleArgument_ShouldThrowException)
{
    Vector arguments(1);
    Vector parameters(1);

    ASSERT_THROW(Functions::SplineBase interpolationSplineBase(arguments, parameters), std::runtime_error);
}

TEST(SplineBaseTests, Constructor_WithTwoArgumentsAndTwoParameters_ShouldInitTwoArgumentsAndTwoValues)
{
    Vector arguments(2);
    Vector parameters(2);
    arguments << 1.0, 2.0;
    parameters << 2.0, 4.0;

    Functions::SplineBase interpolationSplineBase(arguments, parameters);

    EXPECT_EQ(1.0, interpolationSplineBase.GetArgument(0));
    EXPECT_EQ(2.0, interpolationSplineBase.GetValue(0));
    EXPECT_EQ(2.0, interpolationSplineBase.GetArgument(1));
    EXPECT_EQ(4.0, interpolationSplineBase.GetValue(1));
}

TEST(SplineBaseTests, FindIntervalOfArgument_WithArgumentOutsideOfDomain_ShouldThrowException)
{
    Vector arguments(2);
    Vector parameters(2);
    arguments << 1.0, 2.0;
    parameters << 2.0, 4.0;

    Functions::SplineBase interpolationSplineBase(arguments, parameters);

    auto argument = 3.0;
    ASSERT_THROW(interpolationSplineBase.FindIntervalOfArgument(arguments, argument), std::runtime_error);
}

TEST(SplineBaseTests, FindIntervalOfArgument_WithArgumentInsideOfDomain_ShouldReturnInterval)
{
    Vector arguments(2);
    Vector parameters(2);
    arguments << 1.0, 2.0;
    parameters << 2.0, 4.0;

    Functions::SplineBase interpolationSplineBase(arguments, parameters);

    auto argument = 1.5;
    auto&& [index1, index2] = interpolationSplineBase.FindIntervalOfArgument(arguments, argument);

    EXPECT_EQ(index1, 0);
    EXPECT_EQ(index2, 1);
}

TEST(SplineBaseTests, FindIntervalOfArgument_WithArgumentBeingFirstEndpoint_ShouldReturnFirstInterval)
{
    Vector arguments(3);
    Vector parameters(3);
    arguments << 1.0, 2.0, 3.0;
    parameters << 2.0, 4.0, 6.0;

    Functions::SplineBase interpolationSplineBase(arguments, parameters);

    auto argument = 1.0;
    auto&& [index1, index2] = interpolationSplineBase.FindIntervalOfArgument(arguments, argument);

    EXPECT_EQ(index1, 0);
    EXPECT_EQ(index2, 1);
}

TEST(SplineBaseTests, FindIntervalOfArgument_WithArgumentBeingLastEndpoint_ShouldReturnLastInterval)
{
    Vector arguments(3);
    Vector parameters(3);
    arguments << 1.0, 2.0, 3.0;
    parameters << 2.0, 4.0, 6.0;

    Functions::SplineBase interpolationSplineBase(arguments, parameters);

    auto argument = 3.0;
    auto&& [index1, index2] = interpolationSplineBase.FindIntervalOfArgument(arguments, argument);

    EXPECT_EQ(index1, 1);
    EXPECT_EQ(index2, 2);
}
