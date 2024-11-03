#pragma once
#include "IFunctionalFactory.h"
#include "Functionals/L2NormDifferenceFunctional.h"

namespace Functionals
{
class L2NormDifferenceFunctionalFactory : public IFunctionalFactory, public Functionals::FunctionalBase
{
public:
    L2NormDifferenceFunctionalFactory(const std::vector<Functionals::FunctionPointAndValue>& functionValueTable)
        : Functionals::FunctionalBase(functionValueTable)
    {}

    std::unique_ptr<Functionals::IFunctional> CreateFunctional() const override
    {
        return std::make_unique<Functionals::L2NormDifferenceFunctional>(m_functionValueTable);
    }

    ~L2NormDifferenceFunctionalFactory() override = default;
};
}
