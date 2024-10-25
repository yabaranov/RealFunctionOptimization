#pragma once

#include <memory>

namespace Functions
{
class IParametricFunction;
}

namespace Functionals
{
class IFunctional;
}

class FunctionAndFunctionalAbstractFactory
{
public:
    virtual std::unique_ptr<Functions::IParametricFunction> CreateParametricFunction() const = 0;
    virtual std::unique_ptr<Functionals::IFunctional> CreateFunctional() const = 0;
    virtual ~FunctionAndFunctionalAbstractFactory() = default;
};
