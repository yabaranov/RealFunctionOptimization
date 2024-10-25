#pragma once

#include "FunctionFactory.h"
#include "Functions/InterpolationCubicSpline.h"

class InterpolationCubicSplineFactory : public FunctionFactory
{
public:
    std::unique_ptr<Functions::IParametricFunction> CreateParametricFunction() const override
    {
        return std::make_unique<Functions::InterpolationCubicSpline>();
    }

    ~InterpolationCubicSplineFactory() override = default;
};
