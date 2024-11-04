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
    auto lineFunctionFactory = std::make_unique<LineFunctionFactory>();
    auto optimizator = *GaussNewtonOptimizatorBuilder().SetFunctionFactory(std::move(lineFunctionFactory))
                                                      .SetFunctional(std::move(LineFunctional))
                                                      .SetMaxIterations(MaxIterations)
                                                      .SetMaxResidual(MaxResidual)
                                                      .Build();

    Vector parameters = optimizator->Minimize(LINE_INITIAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(GaussNewtonL2NormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL2Functional_ShouldMinimize)
{
    auto piecewiseLineFunctionFactory = std::make_unique<PiecewiseLineFunctionFactory>(SPLINE_ARGUMENTS);   
    auto optimizator = *GaussNewtonOptimizatorBuilder().SetFunctionFactory(std::move(piecewiseLineFunctionFactory))
                                                      .SetFunctional(std::move(SplineFunctional))
                                                      .SetMaxIterations(MaxIterations)
                                                      .SetMaxResidual(MaxResidual)
                                                      .Build();

    Vector parameters = optimizator->Minimize(SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}
