#pragma once
#include "FunctionalFactory.h"
#include "Functionals/MonteCarloIntegralFunctional.h"

class MonteCarloIntegralFunctionalFactory : public FunctionalFactory, public Functionals::FunctionalBase
{
public:
    MonteCarloIntegralFunctionalFactory(const Functionals::IntegralHyperBoxDomain& domain,
                                        uint32_t samples,
                                        uint32_t seed,
                                        const std::vector<Functionals::FunctionPointAndValue>& functionValueTable)
        : Functionals::FunctionalBase(functionValueTable),
          m_domain(domain),
          m_samples(samples),
          m_seed(seed)
    {}

    std::unique_ptr<Functionals::IFunctional> CreateFunctional() const override
    {
        return std::make_unique<Functionals::MonteCarloIntegralFunctional>(m_domain, m_samples, m_seed, m_functionValueTable);
    }

    ~MonteCarloIntegralFunctionalFactory() override = default;

private:
    Functionals::IntegralHyperBoxDomain m_domain;
    uint32_t m_samples;
    uint32_t m_seed;
};
