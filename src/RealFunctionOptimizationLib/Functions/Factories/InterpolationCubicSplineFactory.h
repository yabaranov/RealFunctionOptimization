#pragma once

#include "IFunctionFactory.h"
#include "Functions/InterpolationCubicSpline.h"

namespace Functions
{
class InterpolationCubicSplineFactory : public IFunctionFactory
{
public:
    InterpolationCubicSplineFactory(const Vector& arguments) : m_arguments(arguments)
    {}

    std::unique_ptr<Functions::IFunction> CreateFunction(const Vector& parameters) const override
    {
        return std::make_unique<Functions::InterpolationCubicSpline>(m_arguments, parameters);
    }

    ~InterpolationCubicSplineFactory() override = default;

private:
    Vector m_arguments;
};
}
