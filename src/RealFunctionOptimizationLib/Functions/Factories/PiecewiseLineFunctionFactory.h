#pragma once

#include "IDifferentiableFunctionFactory.h"
#include "Functions/PiecewiseLineFunction.h"

namespace Functions
{
class PiecewiseLineFunctionFactory : public IDifferentiableFunctionFactory
{
public:
    PiecewiseLineFunctionFactory(const Vector& arguments) : m_arguments(arguments)
    {}

    std::unique_ptr<Functions::IFunction> CreateFunction(const Vector& parameters) const override
    {
        return std::make_unique<Functions::PiecewiseLineFunction>(m_arguments, parameters);
    }

    ~PiecewiseLineFunctionFactory() override = default;

private:
    Vector m_arguments;
};
}
