#include <gtest/gtest.h>

#include "OptimizatorsTestsCommon.h"
#include "Functions/InterpolationCubicSpline.h"
#include "Functions/LineFunction.h"
#include "Functions/PiecewiseLineFunction.h"
#include "Optimizators/MonteCarloOptimizator.h"

static constexpr uint32_t SEED = 0;
static constexpr double TOLERANCE = 1e-1;

class MonteCarloL1NormOptimizationTests : public L1NormOptimizationTests{};
class MonteCarloL2NormOptimizationTests : public L2NormOptimizationTests{};
class MonteCarloLInfNormOptimizationTests : public LInfNormOptimizationTests{};
class MonteCarloIntegralOptimizationTests : public IntegralFunctionalOptimizationTests{};

using namespace Optimizators;
using namespace Functions;
using namespace Functionals;

TEST_F(MonteCarloL1NormOptimizationTests, Minimize_WithLineFunctionAndL1Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<MonteCarloOptimizator>(MaxIterations, MaxResidual, SEED);
    LineFunction lineFunction;
    Vector parameters = optimizator->Minimize(*LineFunctional, lineFunction, LINE_INITIAL_PARAMETERS);
    
    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(MonteCarloL1NormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL1Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<MonteCarloOptimizator>(MaxIterations, MaxResidual, SEED);

    PiecewiseLineFunction lineFunction{SPLINE_ARGUMENTS};
    Vector parameters = optimizator->Minimize(*SplineFunctional, lineFunction, SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}

TEST_F(MonteCarloL1NormOptimizationTests, Minimize_WithInterpolationCubicSplineFunctionAndL1Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<MonteCarloOptimizator>(MaxIterations, MaxResidual, SEED);

    InterpolationCubicSpline cubicSpline{CUBIC_SPLINE_ARGUMENTS};
    Vector parameters = optimizator->Minimize(*CubicSplineFunctional, cubicSpline, CUBIC_SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsZigZagXTable[i].value, TOLERANCE);
}

TEST_F(MonteCarloL2NormOptimizationTests, Minimize_WithLineFunctionAndL2Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<MonteCarloOptimizator>(MaxIterations, MaxResidual, SEED);
    LineFunction lineFunction;
    Vector parameters = optimizator->Minimize(*LineFunctional, lineFunction, LINE_INITIAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(MonteCarloL2NormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL2Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<MonteCarloOptimizator>(MaxIterations, MaxResidual, SEED);

    PiecewiseLineFunction lineFunction{SPLINE_ARGUMENTS};
    Vector parameters = optimizator->Minimize(*SplineFunctional, lineFunction, SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}

TEST_F(MonteCarloL2NormOptimizationTests, Minimize_WithInterpolationCubicSplineFunctionAndL1Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<MonteCarloOptimizator>(MaxIterations, MaxResidual, SEED);

    InterpolationCubicSpline cubicSpline{CUBIC_SPLINE_ARGUMENTS};
    Vector parameters = optimizator->Minimize(*CubicSplineFunctional, cubicSpline, CUBIC_SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsZigZagXTable[i].value, TOLERANCE);
}

TEST_F(MonteCarloLInfNormOptimizationTests, Minimize_WithLineFunctionAndLInfFunctional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<MonteCarloOptimizator>(MaxIterations, MaxResidual, SEED);
    LineFunction lineFunction;
    Vector parameters = optimizator->Minimize(*LineFunctional, lineFunction, LINE_INITIAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(MonteCarloLInfNormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL2Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<MonteCarloOptimizator>(MaxIterations, MaxResidual, SEED);

    PiecewiseLineFunction lineFunction{SPLINE_ARGUMENTS};
    Vector parameters = optimizator->Minimize(*SplineFunctional, lineFunction, SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}

TEST_F(MonteCarloLInfNormOptimizationTests, Minimize_WithInterpolationCubicSplineFunctionAndL1Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<MonteCarloOptimizator>(MaxIterations, MaxResidual, SEED);

    InterpolationCubicSpline cubicSpline{CUBIC_SPLINE_ARGUMENTS};
    Vector parameters = optimizator->Minimize(*CubicSplineFunctional, cubicSpline, CUBIC_SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsZigZagXTable[i].value, TOLERANCE);
}

TEST_F(MonteCarloIntegralOptimizationTests, Minimize_WithIntegralFunctional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<MonteCarloOptimizator>(MaxIterations, MaxResidual, SEED);

    IntegralFunction function;
    
    Vector parameters = optimizator->Minimize(*Functional, function, INTEGRAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetExpectedMin(), TOLERANCE);
}
