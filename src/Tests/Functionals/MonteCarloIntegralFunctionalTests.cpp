#include <numbers>
#include <gtest/gtest.h>

#include "Functionals/MonteCarloIntegralFunctional.h"
#include "Functions/IFunction.h"

using namespace Functions;
using namespace Functionals;

namespace
{
class ConstantFunction : public IFunction
{
public:
    double Value(const Vector& point) override
    {
        return 1.0;
    }
};
class SinFunction : public IFunction
{
public:
    double Value(const Vector& point) override
    {
        return std::sin(point[0]);
    }
};

Vector DomainMin = Vector{{0.0}};
Vector DomainMax = Vector{{std::numbers::pi}};
}

TEST(MonteCarloIntegralFunctionalTests, FunctionalValue_WithOneDConstantAsFunction_ShouldReturnLength)
{
    ConstantFunction constant;
    static constexpr uint32_t SEED = 0;
    static constexpr uint32_t SAMPLES = 5;
    MonteCarloIntegralFunctional functional(
        IntegralHyperBoxDomain{.MinParameters = DomainMin, .MaxParameters = DomainMax},
        SAMPLES, SEED);

    ASSERT_NEAR(functional.Value(constant), (DomainMax - DomainMin)[0], 1e-1);
}

TEST(MonteCarloIntegralFunctionalTests, FunctionalValue_WithSinAsFunction_ShouldReturnIntegralOfSin)
{
    SinFunction sinFunction;
    static constexpr uint32_t SEED = 0;
    static constexpr uint32_t SAMPLES = 100;
    static constexpr double EXPECTED_VALUE = 2.0;
    MonteCarloIntegralFunctional functional(
        IntegralHyperBoxDomain{.MinParameters = DomainMin, .MaxParameters = DomainMax},
        SAMPLES, SEED);

    ASSERT_NEAR(functional.Value(sinFunction), EXPECTED_VALUE, 1e-1);
}