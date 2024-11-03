#pragma once

#include "IFunction.h"
#include "InterpolationSplineBase.h"

namespace Functions
{
class InterpolationCubicSpline : public IFunction, public InterpolationSplineBase
{
public:
   InterpolationCubicSpline(const Vector& arguments, const Vector& parameters);
   double Value(const Vector& point) override;

private:
   double GetSplineCoefficient(size_t index);
};
}
