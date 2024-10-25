#pragma once

#include "FunctionAndFunctionalAbstractFactory.h"
#include "Functionals/IFunctional.h"
#include "Functions/IFunction.h"
#include "Factories/FunctionFactories/FunctionFactory.h"
#include "Factories/FunctionalFactories/FunctionalFactory.h"

class FunctionAndFunctionalFactory : public FunctionAndFunctionalAbstractFactory
{
public:
    FunctionAndFunctionalFactory(FunctionFactory& functionFactory,
                                 FunctionalFactory& functionalFactory)
        : m_functionFactory(functionFactory),
          m_functionalFactory(functionalFactory)
    {}

    std::unique_ptr<Functions::IParametricFunction> CreateParametricFunction() const override
    {
        return m_functionFactory.CreateParametricFunction();
    }

    std::unique_ptr<Functionals::IFunctional> CreateFunctional() const override
    {
        return m_functionalFactory.CreateFunctional();
    }

    ~FunctionAndFunctionalFactory() override = default;

private:
    FunctionFactory& m_functionFactory;
    FunctionalFactory& m_functionalFactory;
};
