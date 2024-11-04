#include <gtest/gtest.h>

#include "OptimizatorsTestsCommon.h"
#include "Functions/Factories/InterpolationCubicSplineFactory.h"
#include "Functions/Factories/LineFunctionFactory.h"
#include "Functions/Factories/PiecewiseLineFunctionFactory.h"
#include "Functions/Factories/PolynomialFunctionFactory.h"
#include "Optimizators/MonteCarloOptimizator.h"
#include "Optimizators/Builders/MonteCarloOptimizatorBuilder.h"

static constexpr uint32_t SEED = 0;

class MonteCarloL1NormOptimizationTests : public L1NormOptimizationTests{};
class MonteCarloL2NormOptimizationTests : public L2NormOptimizationTests{};
class MonteCarloLInfNormOptimizationTests : public LInfNormOptimizationTests{};
class MonteCarloIntegralOptimizationTests : public IntegralFunctionalOptimizationTests{};

using namespace Optimizators;
using namespace Functions;
using namespace Functionals;

TEST_F(MonteCarloL1NormOptimizationTests, Minimize_WithLineFunctionAndL1Functional_ShouldMinimize)
{
    auto lineFunctionFactory = std::make_unique<LineFunctionFactory>();
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(lineFunctionFactory))
                                                     .SetFunctional(std::move(LineFunctional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(LINE_INITIAL_PARAMETERS);
    
    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(MonteCarloL1NormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL1Functional_ShouldMinimize)
{
    auto piecewiseLineFunctionFactory = std::make_unique<PiecewiseLineFunctionFactory>(SPLINE_ARGUMENTS);
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(piecewiseLineFunctionFactory))
                                                     .SetFunctional(std::move(SplineFunctional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}

TEST_F(MonteCarloL1NormOptimizationTests, Minimize_WithInterpolationCubicSplineFunctionAndL1Functional_ShouldMinimize)
{
    auto interpolationCubicSplineFactory = std::make_unique<InterpolationCubicSplineFactory>(CUBIC_SPLINE_ARGUMENTS);
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(interpolationCubicSplineFactory))
                                                     .SetFunctional(std::move(CubicSplineFunctional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(CUBIC_SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsZigZagXTable[i].value, TOLERANCE);
}

TEST_F(MonteCarloL1NormOptimizationTests, Minimize_WithPolynomialFunctionAndL1Functional_ShouldMinimize)
{
    auto polynomialFunctionFactory = std::make_unique<PolynomialFunctionFactory>();
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(polynomialFunctionFactory))
                                                     .SetFunctional(std::move(PolynomialFunctional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(POLYNOMIAL_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], GetMinimizingPolynomialYIsSquareX(i), TOLERANCE);
}

TEST_F(MonteCarloL2NormOptimizationTests, Minimize_WithLineFunctionAndL2Functional_ShouldMinimize)
{
    auto lineFunctionFactory = std::make_unique<LineFunctionFactory>();
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(lineFunctionFactory))
                                                     .SetFunctional(std::move(LineFunctional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(LINE_INITIAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(MonteCarloL2NormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL2Functional_ShouldMinimize)
{
    auto piecewiseLineFunctionFactory = std::make_unique<PiecewiseLineFunctionFactory>(SPLINE_ARGUMENTS);
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(piecewiseLineFunctionFactory))
                                                     .SetFunctional(std::move(SplineFunctional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}

TEST_F(MonteCarloL2NormOptimizationTests, Minimize_WithInterpolationCubicSplineFunctionAndL2Functional_ShouldMinimize)
{
    auto interpolationCubicSplineFactory = std::make_unique<InterpolationCubicSplineFactory>(CUBIC_SPLINE_ARGUMENTS);
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(interpolationCubicSplineFactory))
                                                     .SetFunctional(std::move(CubicSplineFunctional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(CUBIC_SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsZigZagXTable[i].value, TOLERANCE);
}

TEST_F(MonteCarloL2NormOptimizationTests, Minimize_WithPolynomialFunctionAndL2Functional_ShouldMinimize)
{
    auto polynomialFunctionFactory = std::make_unique<PolynomialFunctionFactory>();
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(polynomialFunctionFactory))
                                                     .SetFunctional(std::move(PolynomialFunctional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(POLYNOMIAL_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], GetMinimizingPolynomialYIsSquareX(i), TOLERANCE);
}

TEST_F(MonteCarloLInfNormOptimizationTests, Minimize_WithLineFunctionAndLInfFunctional_ShouldMinimize)
{
    auto lineFunctionFactory = std::make_unique<LineFunctionFactory>();
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(lineFunctionFactory))
                                                     .SetFunctional(std::move(LineFunctional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(LINE_INITIAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(MonteCarloLInfNormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL2Functional_ShouldMinimize)
{
    auto piecewiseLineFunctionFactory = std::make_unique<PiecewiseLineFunctionFactory>(SPLINE_ARGUMENTS);
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(piecewiseLineFunctionFactory))
                                                     .SetFunctional(std::move(SplineFunctional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}

TEST_F(MonteCarloLInfNormOptimizationTests, Minimize_WithInterpolationCubicSplineFunctionAndLInfFunctional_ShouldMinimize)
{
    auto interpolationCubicSplineFactory = std::make_unique<InterpolationCubicSplineFactory>(CUBIC_SPLINE_ARGUMENTS);
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(interpolationCubicSplineFactory))
                                                     .SetFunctional(std::move(CubicSplineFunctional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(CUBIC_SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsZigZagXTable[i].value, TOLERANCE);
}

TEST_F(MonteCarloLInfNormOptimizationTests, Minimize_WithPolynomialFunctionAndLInfFunctional_ShouldMinimize)
{
    auto polynomialFunctionFactory = std::make_unique<PolynomialFunctionFactory>();
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(polynomialFunctionFactory))
                                                     .SetFunctional(std::move(PolynomialFunctional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(POLYNOMIAL_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], GetMinimizingPolynomialYIsSquareX(i), TOLERANCE);
}

TEST_F(MonteCarloIntegralOptimizationTests, Minimize_WithIntegralFunctional_ShouldMinimize)
{
    auto integralFunctionFactory = std::make_unique<IntegralFunctionFactory>();
    auto optimizator = *MonteCarloOptimizatorBuilder().SetFunctionFactory(std::move(integralFunctionFactory))
                                                     .SetFunctional(std::move(Functional))
                                                     .SetMaxIterations(MaxIterations)
                                                     .SetMaxResidual(MaxResidual)
                                                     .SetSeed(SEED)
                                                     .Build();

    Vector parameters = optimizator->Minimize(INTEGRAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetExpectedMin(), TOLERANCE);
}
