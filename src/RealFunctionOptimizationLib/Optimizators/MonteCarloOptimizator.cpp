#include "MonteCarloOptimizator.h"

#include "Functionals/IFunctional.h"
#include "Functions/IFunction.h"
#include "Functions/Factories/IFunctionFactory.h"

namespace Optimizators
{
using namespace Functions;
using namespace Functionals;

Vector MonteCarloOptimizator::Minimize(const Vector& initialParameters, Vector* minimumParameters, Vector* maximumParameters)
{
    Vector parameters = initialParameters;
    Vector minParameters = initialParameters;

    std::vector<std::uniform_real_distribution<>> distributions;
    distributions.reserve(parameters.size());
    for (uint32_t i = 0; i < parameters.size(); i++)
        distributions.emplace_back(
            minimumParameters ? (*minimumParameters)[i] : -1.0f,
            maximumParameters ? (*maximumParameters)[i] :  1.0f);

    double currentMin = m_functional->Value(*m_functionFactory->CreateFunction(parameters));

    for (uint32_t i = 0; i < m_maxIterations; i++)
    {
        // pick new parameters randomly
        for (uint32_t paramIndex = 0; paramIndex < parameters.size(); paramIndex++)
            parameters[paramIndex] = distributions[paramIndex](m_randomNumberGenerator);

        const double val = m_functional->Value(*m_functionFactory->CreateFunction(parameters));
        if (val < currentMin)
        {
            currentMin = val;
            minParameters = parameters;
        }
    
        if (currentMin < m_maxResidual)
            break;
    }

    return minParameters;
}

void MonteCarloOptimizator::SetFunctional(std::unique_ptr<Functionals::IFunctional> functional)
{
    m_functional = std::move(functional);
}

void MonteCarloOptimizator::SetFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory)
{
    m_functionFactory = std::move(functionFactory);
}

void MonteCarloOptimizator::SetSeed(uint32_t seed)
{
    m_randomNumberGenerator.seed(seed);
}
}
