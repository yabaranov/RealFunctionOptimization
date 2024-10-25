#pragma once

#include <memory>

namespace Functions
{
class IParametricFunction;
}

class FunctionFactory
{
public:
    virtual std::unique_ptr<Functions::IParametricFunction> CreateParametricFunction() const = 0;
    virtual ~FunctionFactory() = default;
};

