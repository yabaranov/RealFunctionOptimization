#pragma once

#include "FunctionAndFunctionalAbstractFactory.h"
#include "Functionals/IFunctional.h"
#include "Functions/IFunction.h"
#include "Factories/FunctionFactories/DifferentiableFunctionFactory.h"
#include "Factories/FunctionalFactories/DifferentiableFunctionalFactory.h"

class DifferentiableFunctionAndFunctionalFactory : public FunctionAndFunctionalAbstractFactory
{
public:
    DifferentiableFunctionAndFunctionalFactory(DifferentiableFunctionFactory& differentiableFunctionFactory,
                                               DifferentiableFunctionalFactory& differentiableFunctionalFactory)
        : m_differentiableFunctionFactory(differentiableFunctionFactory),
          m_differentiableFunctionalFactory(differentiableFunctionalFactory)
    {}

    std::unique_ptr<Functions::IParametricFunction> CreateParametricFunction() const override
    {
        return m_differentiableFunctionFactory.CreateParametricFunction();
    }

    std::unique_ptr<Functionals::IFunctional> CreateFunctional() const override
    {
        return m_differentiableFunctionalFactory.CreateFunctional();
    }

    ~DifferentiableFunctionAndFunctionalFactory() override = default;

private:
    DifferentiableFunctionFactory& m_differentiableFunctionFactory;
    DifferentiableFunctionalFactory& m_differentiableFunctionalFactory;
};
