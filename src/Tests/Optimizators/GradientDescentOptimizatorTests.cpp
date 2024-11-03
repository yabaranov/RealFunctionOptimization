#include <gtest/gtest.h>

#include "OptimizatorsTestsCommon.h"
#include "Functions/Factories/LineFunctionFactory.h"
#include "Functions/Factories/PiecewiseLineFunctionFactory.h"
#include "Optimizators/Builders/GradientDescentOptimizatorBuilder.h"
#include "Optimizators/GradientDescentOptimizator.h"

class GradientDescentL1NormOptimizationTests : public L1NormOptimizationTests{};
class GradientDescentL2NormOptimizationTests : public L2NormOptimizationTests{};

using namespace Optimizators;
using namespace Functions;
using namespace Functionals;

TEST_F(GradientDescentL1NormOptimizationTests, Minimize_WithLineFunctionAndL1Functional_ShouldMinimize)
{
    GradientDescentOptimizatorBuilder gradientDescentOptimizatorBuilder;
    auto lineFunctionFactory = std::make_unique<LineFunctionFactory>();

    auto optimizator = gradientDescentOptimizatorBuilder.setFunctionFactory(std::move(lineFunctionFactory))
                                                        .setFunctional(std::move(LineFunctional))
                                                        .setMaxIterations(MaxIterations)
                                                        .setMaxResidual(MaxResidual)
                                                        .getOptimizator();

    Vector parameters = optimizator->Minimize(LINE_INITIAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(GradientDescentL1NormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL1Functional_ShouldMinimize)
{
    GradientDescentOptimizatorBuilder gradientDescentOptimizatorBuilder;
    auto piecewiseLineFunctionFactory = std::make_unique<PiecewiseLineFunctionFactory>(SPLINE_ARGUMENTS);

    auto optimizator = gradientDescentOptimizatorBuilder.setFunctionFactory(std::move(piecewiseLineFunctionFactory))
                                                        .setFunctional(std::move(SplineFunctional))
                                                        .setMaxIterations(MaxIterations)
                                                        .setMaxResidual(MaxResidual)
                                                        .getOptimizator();

    Vector parameters = optimizator->Minimize(SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}

TEST_F(GradientDescentL2NormOptimizationTests, Minimize_WithLineFunctionAndL2Functional_ShouldMinimize)
{
    GradientDescentOptimizatorBuilder gradientDescentOptimizatorBuilder;
    auto lineFunctionFactory = std::make_unique<LineFunctionFactory>();

    auto optimizator = gradientDescentOptimizatorBuilder.setFunctionFactory(std::move(lineFunctionFactory))
                                                        .setFunctional(std::move(LineFunctional))
                                                        .setMaxIterations(MaxIterations)
                                                        .setMaxResidual(MaxResidual)
                                                        .getOptimizator();

    Vector parameters = optimizator->Minimize(LINE_INITIAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(GradientDescentL2NormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL2Functional_ShouldMinimize)
{
    GradientDescentOptimizatorBuilder gradientDescentOptimizatorBuilder;
    auto piecewiseLineFunctionFactory = std::make_unique<PiecewiseLineFunctionFactory>(SPLINE_ARGUMENTS);

    auto optimizator = gradientDescentOptimizatorBuilder.setFunctionFactory(std::move(piecewiseLineFunctionFactory))
                                                        .setFunctional(std::move(SplineFunctional))
                                                        .setMaxIterations(MaxIterations)
                                                        .setMaxResidual(MaxResidual)
                                                        .getOptimizator();

    Vector parameters = optimizator->Minimize(SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}
