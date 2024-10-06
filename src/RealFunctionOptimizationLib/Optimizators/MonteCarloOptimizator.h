#pragma once

#include "IOptimizator.h"

#include <random>

namespace Optimizators
{
class MonteCarloOptimizator :  public IOptimizator, public OptimizatorBase
{
public:
    MonteCarloOptimizator(uint32_t maxIterations, double maxResidual, uint32_t seed = std::random_device{}());
    Vector Minimize(Functionals::IFunctional& objective, Functions::IParametricFunction& function,
        const Vector& initialParameters, Vector* minimumParameters, Vector* maximumParameters) override;
private:
    std::mt19937 m_randomNumberGenerator;
};
}
