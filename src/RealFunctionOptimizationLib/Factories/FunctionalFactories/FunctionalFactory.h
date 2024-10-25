#pragma once

#include <memory>

namespace Functionals
{
class IFunctional;
}

class FunctionalFactory
{
public:
    virtual std::unique_ptr<Functionals::IFunctional> CreateFunctional() const = 0;
    virtual ~FunctionalFactory() = default;
};
