#include "MonteCarloOptimizatorBuilder.h"

#include "Optimizators/IOptimizator.h"
#include "Optimizators/MonteCarloOptimizator.h"

#include "Functionals/IFunctional.h"
#include "Functions/Factories/IFunctionFactory.h"

namespace Optimizators
{
MonteCarloOptimizatorBuilder::MonteCarloOptimizatorBuilder()
{
    reset();
}

IOptimizatorBuilder& MonteCarloOptimizatorBuilder::setFunctional(std::unique_ptr<Functionals::IFunctional> functional)
{
    m_monteCarloOptimizator->setFunctional(std::move(functional));
    return *this;
}

IOptimizatorBuilder& MonteCarloOptimizatorBuilder::setFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory)
{
    m_monteCarloOptimizator->setFunctionFactory(std::move(functionFactory));
    return *this;
}

IOptimizatorBuilder& MonteCarloOptimizatorBuilder::setMaxIterations(uint32_t maxIterations)
{
    m_monteCarloOptimizator->setMaxIterations(maxIterations);
    return *this;
}

IOptimizatorBuilder& MonteCarloOptimizatorBuilder::setMaxResidual(double maxResidual)
{
    m_monteCarloOptimizator->setMaxResidual(maxResidual);
    return *this;
}

std::unique_ptr<IOptimizator> MonteCarloOptimizatorBuilder::getOptimizator()
{
    auto optimizator = std::move(m_monteCarloOptimizator);
    reset();
    return optimizator;
}

void MonteCarloOptimizatorBuilder::reset()
{
    m_monteCarloOptimizator.reset();
    m_monteCarloOptimizator = std::make_unique<MonteCarloOptimizator>();
}

IOptimizatorBuilder& MonteCarloOptimizatorBuilder::setSeed(uint32_t seed)
{
    m_monteCarloOptimizator->setSeed(seed);
    return *this;
}
}
