#pragma once

#include "Common.h"
#include "Functions/SplineBase.h"

namespace Functions
{
class CubicSplineImpl : public SplineBase
{
public:
    CubicSplineImpl(const Vector& arguments, const Vector& parameters)
        : SplineBase(arguments, parameters)
    {
        if(parameters.size() < 4)
            throw std::runtime_error("The number of parameters of the cubic spline must be greater than or equal to 4");
    }

    virtual double Value(const Vector& point) = 0;

    virtual ~CubicSplineImpl() = default;

protected:
    std::vector<std::function<double(double, double)>> m_basisFunctions =
    {
        [](double x, double)   { return 1 - 3 * x * x + 2 * x * x * x; },
        [](double x, double h) { return h * (x - 2 * x * x + x * x * x); },
        [](double x, double)   { return 3 * x * x - 2 * x * x * x; },
        [](double x, double h) { return h * (-x * x + x * x * x); },
    };
};
}
