#include <gtest/gtest.h>

#include "OptimizatorsTestsCommon.h"
#include "Functions/InterpolationCubicSpline.h"
#include "Functions/LineFunction.h"
#include "Functions/PiecewiseLineFunction.h"
#include "Functions/PolynomialFunction.h"
#include "Optimizators/GradientDescentOptimizator.h"

class GradientDescentL1NormOptimizationTests : public L1NormOptimizationTests{};
class GradientDescentL2NormOptimizationTests : public L2NormOptimizationTests{};
class GradientDescentLInfNormOptimizationTests : public LInfNormOptimizationTests{};
class GradientDescentIntegralOptimizationTests : public IntegralFunctionalOptimizationTests{};

using namespace Optimizators;
using namespace Functions;
using namespace Functionals;

TEST_F(GradientDescentL1NormOptimizationTests, Minimize_WithLineFunctionAndL1Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);
    LineFunction lineFunction;
    Vector parameters = optimizator->Minimize(*LineFunctional, lineFunction, LINE_INITIAL_PARAMETERS);
    
    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(GradientDescentL1NormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL1Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);

    PiecewiseLineFunction lineFunction{SPLINE_ARGUMENTS};
    Vector parameters = optimizator->Minimize(*SplineFunctional, lineFunction, SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}

TEST_F(GradientDescentL1NormOptimizationTests, Minimize_WithCubicSplineFunctionAndL1Functional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);
    InterpolationCubicSpline lineFunction{CUBIC_SPLINE_ARGUMENTS};
    
    ASSERT_THROW(optimizator->Minimize(*LineFunctional, lineFunction, CUBIC_SPLINE_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GradientDescentL1NormOptimizationTests, Minimize_WithPolynomialFunctionAndL1Functional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);
    PolynomialFunction polynomialFunction;

    ASSERT_THROW(optimizator->Minimize(*PolynomialFunctional, polynomialFunction, POLYNOMIAL_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GradientDescentL2NormOptimizationTests, Minimize_WithLineFunctionAndL2Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);
    LineFunction lineFunction;
    Vector parameters = optimizator->Minimize(*LineFunctional, lineFunction, LINE_INITIAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(GradientDescentL2NormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL2Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);

    PiecewiseLineFunction lineFunction{SPLINE_ARGUMENTS};
    Vector parameters = optimizator->Minimize(*SplineFunctional, lineFunction, SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}

TEST_F(GradientDescentL2NormOptimizationTests, Minimize_WithInterpolationCubicSplineFunctionAndL2Functional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);

    InterpolationCubicSpline cubicSpline{CUBIC_SPLINE_ARGUMENTS};

    ASSERT_THROW(optimizator->Minimize(*LineFunctional, cubicSpline, CUBIC_SPLINE_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GradientDescentL2NormOptimizationTests, Minimize_WithPolynomialFunctionAndL2Functional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);
    PolynomialFunction polynomialFunction;

    ASSERT_THROW(optimizator->Minimize(*PolynomialFunctional, polynomialFunction, POLYNOMIAL_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GradientDescentLInfNormOptimizationTests, Minimize_WithLineFunctionAndLInfFunctional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);
    LineFunction lineFunction;

    ASSERT_THROW(optimizator->Minimize(*LineFunctional, lineFunction, LINE_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GradientDescentLInfNormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndLInfFunctional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);
    PiecewiseLineFunction lineFunction{SPLINE_ARGUMENTS};
    
    ASSERT_THROW(optimizator->Minimize(*LineFunctional, lineFunction, SPLINE_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GradientDescentLInfNormOptimizationTests, Minimize_WithCubicSplineFunctionAndLInfFunctional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);
    InterpolationCubicSpline lineFunction{CUBIC_SPLINE_ARGUMENTS};
    
    ASSERT_THROW(optimizator->Minimize(*LineFunctional, lineFunction, CUBIC_SPLINE_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GradientDescentLInfNormOptimizationTests, Minimize_WithPolynomialFunctionAndLInfFunctional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);
    PolynomialFunction polynomialFunction;

    ASSERT_THROW(optimizator->Minimize(*PolynomialFunctional, polynomialFunction, POLYNOMIAL_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GradientDescentIntegralOptimizationTests, Minimize_WithIntegralFunctional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GradientDescentOptimizator>(MaxIterations, MaxResidual);
    IntegralFunction function;
    
    ASSERT_THROW(optimizator->Minimize(*Functional, function, INTEGRAL_PARAMETERS), std::runtime_error);
}
