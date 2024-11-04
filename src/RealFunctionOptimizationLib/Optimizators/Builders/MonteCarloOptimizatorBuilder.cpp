#include "MonteCarloOptimizatorBuilder.h"

#include "Optimizators/IOptimizator.h"
#include "Optimizators/MonteCarloOptimizator.h"

#include "Functionals/IFunctional.h"
#include "Functions/Factories/IFunctionFactory.h"

namespace Optimizators
{
MonteCarloOptimizatorBuilder::MonteCarloOptimizatorBuilder()
{
    Reset();
}

MonteCarloOptimizatorBuilder& MonteCarloOptimizatorBuilder::SetFunctional(std::unique_ptr<Functionals::IFunctional> functional)
{
    m_monteCarloOptimizator->SetFunctional(std::move(functional));
    return *this;
}

MonteCarloOptimizatorBuilder& MonteCarloOptimizatorBuilder::SetFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory)
{
    m_monteCarloOptimizator->SetFunctionFactory(std::move(functionFactory));
    return *this;
}

MonteCarloOptimizatorBuilder& MonteCarloOptimizatorBuilder::SetMaxIterations(uint32_t maxIterations)
{
    m_monteCarloOptimizator->SetMaxIterations(maxIterations);
    return *this;
}

MonteCarloOptimizatorBuilder& MonteCarloOptimizatorBuilder::SetMaxResidual(double maxResidual)
{
    m_monteCarloOptimizator->SetMaxResidual(maxResidual);
    return *this;
}

std::unique_ptr<IOptimizator> MonteCarloOptimizatorBuilder::Build()
{
    auto optimizator = std::move(m_monteCarloOptimizator);
    Reset();
    return optimizator;
}

void MonteCarloOptimizatorBuilder::Reset()
{
    m_monteCarloOptimizator = std::make_unique<MonteCarloOptimizator>();
}

MonteCarloOptimizatorBuilder& MonteCarloOptimizatorBuilder::SetSeed(uint32_t seed)
{
    m_monteCarloOptimizator->SetSeed(seed);
    return *this;
}
}
