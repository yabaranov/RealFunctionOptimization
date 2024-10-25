#pragma once

#include "FunctionFactory.h"
#include "Functions/PolynomialFunction.h"

class PolynomialFunctionFactory : public FunctionFactory
{
public:
    std::unique_ptr<Functions::IParametricFunction> CreateParametricFunction() const override
    {
        return std::make_unique<Functions::PolynomialFunction>();
    }

    ~PolynomialFunctionFactory() override = default;
};
