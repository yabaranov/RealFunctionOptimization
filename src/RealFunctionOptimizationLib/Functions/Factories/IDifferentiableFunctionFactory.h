#pragma once

#include "IFunctionFactory.h"

namespace Functions
{
class IDifferentiableFunctionFactory : public IFunctionFactory
{
public:
    virtual ~IDifferentiableFunctionFactory() override = default;
};
}
