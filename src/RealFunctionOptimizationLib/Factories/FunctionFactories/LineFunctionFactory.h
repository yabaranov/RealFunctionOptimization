#pragma once

#include "DifferentiableFunctionFactory.h"
#include "Functions/LineFunction.h"

class LineFunctionFactory : public DifferentiableFunctionFactory
{
public:
    std::unique_ptr<Functions::IParametricFunction> CreateParametricFunction() const override
    {
        return std::make_unique<Functions::LineFunction>();
    }

    ~LineFunctionFactory() override = default;
};
