#pragma once

#include <random>

#include "IFunctional.h"

namespace Functionals
{
struct IntegralHyperBoxDomain
{
    Vector MinParameters;
    Vector MaxParameters;
};
    
class MonteCarloIntegralFunctional : public IFunctional
{
public:
    MonteCarloIntegralFunctional(const IntegralHyperBoxDomain& domain,
        uint32_t samples, uint32_t seed = std::random_device{}());
    double Value(Functions::IFunction& function) override;
private:
    IntegralHyperBoxDomain m_hyperBoxDomain{};
    uint32_t m_samples{};
    std::mt19937 m_randomNumberGenerator;
};
}
