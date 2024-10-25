#pragma once
#include "FunctionalFactory.h"
#include "Functionals/LInfNormDifferenceFunctional.h"

class LInfNormDifferenceFunctionalFactory : public FunctionalFactory, public Functionals::FunctionalBase
{
public:
    LInfNormDifferenceFunctionalFactory(const std::vector<Functionals::FunctionPointAndValue>& functionValueTable)
        : Functionals::FunctionalBase(functionValueTable)
    {}

    std::unique_ptr<Functionals::IFunctional> CreateFunctional() const override
    {
        return std::make_unique<Functionals::LInfNormDifferenceFunctional>(m_functionValueTable);
    }

    ~LInfNormDifferenceFunctionalFactory() override = default;
};
