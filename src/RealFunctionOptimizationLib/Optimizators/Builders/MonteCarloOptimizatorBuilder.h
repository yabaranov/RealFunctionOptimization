#pragma once
#include "IOptimizatorBuilder.h"

namespace Optimizators
{

class MonteCarloOptimizator;

class MonteCarloOptimizatorBuilder : public IOptimizatorBuilder
{
public:
    MonteCarloOptimizatorBuilder();

    IOptimizatorBuilder& setFunctional(std::unique_ptr<Functionals::IFunctional> functional) override;
    IOptimizatorBuilder& setFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory) override;
    IOptimizatorBuilder& setMaxIterations(uint32_t maxIterations) override;
    IOptimizatorBuilder& setMaxResidual(double maxResidual) override;
    std::unique_ptr<IOptimizator> getOptimizator() override;
    void reset() override;

    IOptimizatorBuilder& setSeed(uint32_t seed);

    ~MonteCarloOptimizatorBuilder() override = default;

private:
    std::unique_ptr<MonteCarloOptimizator> m_monteCarloOptimizator;
};
}
