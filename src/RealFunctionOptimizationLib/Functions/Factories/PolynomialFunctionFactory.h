#pragma once

#include "IFunctionFactory.h"
#include "Functions/PolynomialFunction.h"

namespace Functions
{
class PolynomialFunctionFactory : public IFunctionFactory
{
public:
    std::unique_ptr<Functions::IFunction> CreateFunction(const Vector& parameters) const override
    {
        return std::make_unique<Functions::PolynomialFunction>(parameters);
    }

    ~PolynomialFunctionFactory() override = default;
};
}
