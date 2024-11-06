#pragma once

#include "CubicSplineImpl.h"

namespace Functions
{
class InterpolationCubicSplineImpl : public CubicSplineImpl
{
public:
    InterpolationCubicSplineImpl(const Vector& arguments, const Vector& parameters);
    double Value(const Vector& point) override;

    ~InterpolationCubicSplineImpl() override = default;

private:
    double GetSplineCoefficient(size_t index);
};
}
