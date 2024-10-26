#include <gtest/gtest.h>

#include "OptimizatorsTestsCommon.h"
#include "Functions/LineFunction.h"
#include "Functions/PiecewiseLineFunction.h"
#include "Optimizators/GaussNewtonOptimizator.h"

static constexpr double TOLERANCE = 1e-1;
static const Vector LINE_INITIAL_PARAMETERS = Vector::Constant(1, 0.5);

class GaussNewtonL1NormOptimizationTests : public L1NormOptimizationTests{};
class GaussNewtonL2NormOptimizationTests : public L2NormOptimizationTests{};
class GaussNewtonLInfNormOptimizationTests : public LInfNormOptimizationTests{};

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

TEST_F(GaussNewtonL2NormOptimizationTests, Minimize_WithLineFunctionAndL2Functional_ShouldMinimize)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GaussNewtonOptimizator>(MaxIterations, MaxResidual);
    LineFunction lineFunction;
    Vector parameters = optimizator->Minimize(*LineFunctional, lineFunction, LINE_INITIAL_PARAMETERS);

    EXPECT_NEAR(parameters[0], GetMinimizingLineYIsX(), TOLERANCE);
}

TEST_F(GaussNewtonLInfNormOptimizationTests, Minimize_WithLineFunctionAndLInfFunctional_ShouldThrowException)
{
    std::unique_ptr<IOptimizator> optimizator =
        std::make_unique<GaussNewtonOptimizator>(MaxIterations, MaxResidual);
    LineFunction lineFunction;

    ASSERT_THROW(optimizator->Minimize(*LineFunctional, lineFunction, LINE_INITIAL_PARAMETERS), std::runtime_error);
}
