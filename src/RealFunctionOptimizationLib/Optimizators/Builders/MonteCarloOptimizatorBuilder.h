#pragma once
#include "IOptimizatorBuilder.h"

namespace Optimizators
{

class MonteCarloOptimizator;

class MonteCarloOptimizatorBuilder : public IOptimizatorBuilder
{
public:
    MonteCarloOptimizatorBuilder();

    MonteCarloOptimizatorBuilder& SetFunctional(std::unique_ptr<Functionals::IFunctional> functional) override;
    MonteCarloOptimizatorBuilder& SetFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory) override;
    MonteCarloOptimizatorBuilder& SetMaxIterations(uint32_t maxIterations) override;
    MonteCarloOptimizatorBuilder& SetMaxResidual(double maxResidual) override;
    std::unique_ptr<IOptimizator> Build() override;
    void Reset() override;

    MonteCarloOptimizatorBuilder& SetSeed(uint32_t seed);

    ~MonteCarloOptimizatorBuilder() override = default;

private:
    std::unique_ptr<MonteCarloOptimizator> m_monteCarloOptimizator;
};
}
