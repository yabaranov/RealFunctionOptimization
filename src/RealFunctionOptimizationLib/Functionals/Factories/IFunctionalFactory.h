#pragma once

#include <memory>

namespace Functionals
{
class IFunctional;

class IFunctionalFactory
{
public:
    virtual std::unique_ptr<Functionals::IFunctional> CreateFunctional() const = 0;
    virtual ~IFunctionalFactory() = default;
};
}
