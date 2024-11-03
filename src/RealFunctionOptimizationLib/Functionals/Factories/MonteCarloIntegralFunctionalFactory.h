#pragma once
#include "IFunctionalFactory.h"
#include "Functionals/MonteCarloIntegralFunctional.h"

namespace Functionals
{
class MonteCarloIntegralFunctionalFactory : public IFunctionalFactory
{
public:
    MonteCarloIntegralFunctionalFactory(const Functionals::IntegralHyperBoxDomain& domain,
                                        uint32_t samples,
                                        uint32_t seed = std::random_device{}())
        : m_domain(domain),
          m_samples(samples),
          m_seed(seed)
    {}

    std::unique_ptr<Functionals::IFunctional> CreateFunctional() const override
    {
        return std::make_unique<Functionals::MonteCarloIntegralFunctional>(m_domain, m_samples, m_seed);
    }

    ~MonteCarloIntegralFunctionalFactory() override = default;

private:
    Functionals::IntegralHyperBoxDomain m_domain;
    uint32_t m_samples;
    uint32_t m_seed;
};
}
