#include "MonteCarloOptimizator.h"

#include "Functionals/IFunctional.h"
#include "Functions/IFunction.h"

namespace Optimizators
{
using namespace Functions;
using namespace Functionals;

MonteCarloOptimizator::MonteCarloOptimizator(uint32_t maxIterations, double maxResidual, uint32_t seed)
    : OptimizatorBase(maxIterations, maxResidual), m_randomNumberGenerator(seed)
{
}

Vector MonteCarloOptimizator::Minimize(IFunctional& objective, IParametricFunction& function,
    const Vector& initialParameters, Vector* minimumParameters, Vector* maximumParameters)
{
    Vector parameters = initialParameters;
    Vector minParameters = initialParameters;

    std::vector<std::uniform_real_distribution<>> distributions;
    distributions.reserve(parameters.size());
    for (uint32_t i = 0; i < parameters.size(); i++)
        distributions.emplace_back(
            minimumParameters ? (*minimumParameters)[i] : -1.0f,
            maximumParameters ? (*maximumParameters)[i] :  1.0f);

    double currentMin = objective.Value(*function.Bind(parameters));

    for (uint32_t i = 0; i < m_maxIterations; i++)
    {
        // pick new parameters randomly
        for (uint32_t paramIndex = 0; paramIndex < parameters.size(); paramIndex++)
            parameters[paramIndex] = distributions[paramIndex](m_randomNumberGenerator);

        const double val = objective.Value(*function.Bind(parameters));
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
}
