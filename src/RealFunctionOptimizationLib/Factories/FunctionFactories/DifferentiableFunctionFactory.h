#pragma once

#include <memory>

namespace Functions
{
class IParametricFunction;
}

class DifferentiableFunctionFactory
{
public:
    virtual std::unique_ptr<Functions::IParametricFunction> CreateParametricFunction() const = 0;
    virtual ~DifferentiableFunctionFactory() = default;
};
