#include "MonteCarloIntegralFunctional.h"

#include "Functions/IFunction.h"

Functionals::MonteCarloIntegralFunctional::MonteCarloIntegralFunctional(const IntegralHyperBoxDomain& domain,
    uint32_t samples, uint32_t seed,
    const std::vector<FunctionPointAndValue>& functionPointValues)
        : FunctionalBase(functionPointValues),
    m_hyperBoxDomain(domain),
    m_samples(samples), m_randomNumberGenerator(seed)
{
}

double Functionals::MonteCarloIntegralFunctional::Value(Functions::IFunction& function)
{
    double pdf = 1.0f;
    std::vector<std::uniform_real_distribution<>> distributions;
    distributions.reserve(m_hyperBoxDomain.MinParameters.size());
    for (uint32_t i = 0; i < distributions.size(); i++)
    {
        pdf *= m_hyperBoxDomain.MaxParameters[i] - m_hyperBoxDomain.MinParameters[i];
        distributions.emplace_back(m_hyperBoxDomain.MinParameters[i], m_hyperBoxDomain.MaxParameters[i]);
    }

    Vector samplePoint = Vector::Zero(distributions.size());
    double value = 0.0f;
    for (uint32_t sample = 0; sample < m_samples; sample++)
    {
        for (uint32_t i = 0; i < samplePoint.size(); i++)
            samplePoint[i] = distributions[i](m_randomNumberGenerator);
        
        value += function.Value(samplePoint);
    }

    return value / (pdf * m_samples);
}
