#include <gtest/gtest.h>

#include "OptimizatorsTestsCommon.h"
#include "Functions/InterpolationCubicSpline.h"
#include "Functions/LineFunction.h"
#include "Functions/PiecewiseLineFunction.h"
#include "Optimizators/GaussNewtonOptimizator.h"

static constexpr double TOLERANCE = 1e-1;

class GaussNewtonL1NormOptimizationTests : public L1NormOptimizationTests{};
class GaussNewtonL2NormOptimizationTests : public L2NormOptimizationTests{};
class GaussNewtonLInfNormOptimizationTests : public LInfNormOptimizationTests{};
class GaussNewtonIntegralOptimizationTests : public IntegralFunctionalOptimizationTests{};

using namespace Optimizators;
using namespace Functions;
using namespace Functionals;

TEST_F(GaussNewtonL1NormOptimizationTests, Minimize_WithLineFunctionAndL1Functional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GaussNewtonOptimizator>(MaxIterations, MaxResidual);
    LineFunction lineFunction;
    
    ASSERT_THROW(optimizator->Minimize(*LineFunctional, lineFunction, LINE_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GaussNewtonL1NormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL1Functional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GaussNewtonOptimizator>(MaxIterations, MaxResidual);
    PiecewiseLineFunction lineFunction{SPLINE_ARGUMENTS};
    
    ASSERT_THROW(optimizator->Minimize(*LineFunctional, lineFunction, SPLINE_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GaussNewtonL1NormOptimizationTests, Minimize_WithCubicSplineFunctionAndL1Functional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GaussNewtonOptimizator>(MaxIterations, MaxResidual);
    InterpolationCubicSpline lineFunction{CUBIC_SPLINE_ARGUMENTS};
    
    ASSERT_THROW(optimizator->Minimize(*LineFunctional, lineFunction, CUBIC_SPLINE_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GaussNewtonL2NormOptimizationTests, Minimize_WithLineFunctionAndL2Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GaussNewtonOptimizator>(MaxIterations, MaxResidual);
    LineFunction lineFunction;
    Vector parameters = optimizator->Minimize(*LineFunctional, lineFunction, LINE_INITIAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(GaussNewtonL2NormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndL2Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GaussNewtonOptimizator>(MaxIterations, MaxResidual);

    PiecewiseLineFunction lineFunction{SPLINE_ARGUMENTS};
    Vector parameters = optimizator->Minimize(*SplineFunctional, lineFunction, SPLINE_INITIAL_PARAMETERS);

    for (uint32_t i = 0; i < parameters.size(); i++)
        EXPECT_NEAR(parameters[i], FunctionYIsAbsXTable[i].value, TOLERANCE);
}

TEST_F(GaussNewtonL2NormOptimizationTests, Minimize_WithInterpolationCubicSplineFunctionAndL2Functional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GaussNewtonOptimizator>(MaxIterations, MaxResidual);

    InterpolationCubicSpline cubicSpline{CUBIC_SPLINE_ARGUMENTS};

    ASSERT_THROW(optimizator->Minimize(*LineFunctional, cubicSpline, CUBIC_SPLINE_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GaussNewtonLInfNormOptimizationTests, Minimize_WithLineFunctionAndLInfFunctional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GaussNewtonOptimizator>(MaxIterations, MaxResidual);
    LineFunction lineFunction;

    ASSERT_THROW(optimizator->Minimize(*LineFunctional, lineFunction, LINE_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GaussNewtonLInfNormOptimizationTests, Minimize_WithPiecewiseLineFunctionAndLInfFunctional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GaussNewtonOptimizator>(MaxIterations, MaxResidual);
    PiecewiseLineFunction lineFunction{SPLINE_ARGUMENTS};
    
    ASSERT_THROW(optimizator->Minimize(*LineFunctional, lineFunction, SPLINE_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GaussNewtonLInfNormOptimizationTests, Minimize_WithCubicSplineFunctionAndLInfFunctional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GaussNewtonOptimizator>(MaxIterations, MaxResidual);
    InterpolationCubicSpline lineFunction{CUBIC_SPLINE_ARGUMENTS};
    
    ASSERT_THROW(optimizator->Minimize(*LineFunctional, lineFunction, CUBIC_SPLINE_INITIAL_PARAMETERS), std::runtime_error);
}

TEST_F(GaussNewtonIntegralOptimizationTests, Minimize_WithIntegralFunctional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GaussNewtonOptimizator>(MaxIterations, MaxResidual);
    IntegralFunction function;
    
    ASSERT_THROW(optimizator->Minimize(*Functional, function, INTEGRAL_PARAMETERS), std::runtime_error);
}