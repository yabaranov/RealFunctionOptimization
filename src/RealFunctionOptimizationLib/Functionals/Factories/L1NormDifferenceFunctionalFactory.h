#pragma once
#include "IFunctionalFactory.h"
#include "Functionals/L1NormDifferenceFunctional.h"

namespace Functionals
{
class L1NormDifferenceFunctionalFactory : public IFunctionalFactory, public Functionals::FunctionalBase
{
public:
    L1NormDifferenceFunctionalFactory(const std::vector<Functionals::FunctionPointAndValue>& functionValueTable)
        : Functionals::FunctionalBase(functionValueTable)
    {}

    std::unique_ptr<Functionals::IFunctional> CreateFunctional() const override
    {
        return std::make_unique<Functionals::L1NormDifferenceFunctional>(m_functionValueTable);
    }

    ~L1NormDifferenceFunctionalFactory() override = default;
};
}
