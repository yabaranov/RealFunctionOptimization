#pragma once

#include "IDifferentiableFunctionFactory.h"
#include "Functions/LineFunction.h"

namespace Functions
{
class LineFunctionFactory : public IDifferentiableFunctionFactory
{
public:
    std::unique_ptr<Functions::IFunction> CreateFunction(const Vector& parameters) const override
    {
        return std::make_unique<Functions::LineFunction>(parameters);
    }

    ~LineFunctionFactory() override = default;
};
}
