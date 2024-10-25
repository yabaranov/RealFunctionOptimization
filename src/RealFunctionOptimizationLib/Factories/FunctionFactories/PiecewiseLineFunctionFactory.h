#pragma once

#include "DifferentiableFunctionFactory.h"
#include "Functions/PiecewiseLineFunction.h"

class PiecewiseLineFunctionFactory : public DifferentiableFunctionFactory
{
public:
    std::unique_ptr<Functions::IParametricFunction> CreateParametricFunction() const override
    {
        return std::make_unique<Functions::PiecewiseLineFunction>();
    }

    ~PiecewiseLineFunctionFactory() override = default;
};
