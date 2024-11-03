#include <gtest/gtest.h>

#include "OptimizatorsTestsCommon.h"
#include "Optimizators/Builders/GaussNewtonOptimizatorBuilder.h"
#include "Optimizators/GaussNewtonOptimizator.h"
#include "Functions/Factories/LineFunctionFactory.h"
#include "Functions/Factories/PiecewiseLineFunctionFactory.h"

class GaussNewtonL2NormOptimizationTests : public L2NormOptimizationTests{};

using namespace Optimizators;
using namespace Functions;
using namespace Functionals;

TEST_F(GaussNewtonL2NormOptimizationTests, Minimize_WithLineFunctionAndL2Functional_ShouldMinimize)
{
    GaussNewtonOptimizatorBuilder gaussNewtonOptimizatorBuilder;
    auto lineFunctionFactory = std::make_unique<LineFunctionFactory>();

    auto optimizator = gaussNewtonOptimizatorBuilder.setFunctionFactory(std::move(lineFunctionFactory))
                                                    .setFunctional(std::move(LineFunctional))
                                                    .setMaxIterations(MaxIterations)
                                                    .setMaxResidual(MaxResidual)
                                                    .getOptimizator();

    Vector parameters = optimizator->Minimize(LINE_INITIAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(GaussNewtonL2NormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL2Functional_ShouldMinimize)
{
    GaussNewtonOptimizatorBuilder gaussNewtonOptimizatorBuilder;
    auto piecewiseLineFunctionFactory = std::make_unique<PiecewiseLineFunctionFactory>(SPLINE_ARGUMENTS);

    auto optimizator = gaussNewtonOptimizatorBuilder.setFunctionFactory(std::move(piecewiseLineFunctionFactory))
                                                    .setFunctional(std::move(LineFunctional))
                                                    .setMaxIterations(MaxIterations)
                                                    .setMaxResidual(MaxResidual)
                                                    .getOptimizator();

    Vector parameters = optimizator->Minimize(SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}
