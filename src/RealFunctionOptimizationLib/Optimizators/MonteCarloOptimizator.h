#pragma once

#include "IOptimizator.h"

#include <random>

namespace Functionals
{
class IFunctional;
}

namespace Functions
{
class IFunctionFactory;
}

namespace Optimizators
{
class MonteCarloOptimizator :  public IOptimizator, public OptimizatorBase
{
public:
    MonteCarloOptimizator() = default;
    Vector Minimize(const Vector& initialParameters, Vector* minimumParameters, Vector* maximumParameters) override;
    void SetFunctional(std::unique_ptr<Functionals::IFunctional> functional);
    void SetFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory);
    void SetSeed(uint32_t seed);

private:
    std::unique_ptr<Functionals::IFunctional> m_functional;
    std::unique_ptr<Functions::IFunctionFactory> m_functionFactory;
    std::mt19937 m_randomNumberGenerator{std::random_device{}()};
};
}
