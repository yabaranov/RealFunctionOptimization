#pragma once

#include "Common.h"
#include <memory>

namespace Functions
{
class IFunction;

class IFunctionFactory
{
public:
    virtual std::unique_ptr<Functions::IFunction> CreateFunction(const Vector& parameters) const = 0;
    virtual ~IFunctionFactory() = default;
};
}
