#pragma once

#include "IFunction.h"
#include "InterpolationSplineBase.h"

namespace Functions
{
class PiecewiseLineFunction : public IDifferentiableFunction, public InterpolationSplineBase
{
public:
   PiecewiseLineFunction(const Vector& arguments, const Vector& parameters);
   Vector Gradient(const Vector& point) override;
   double Value(const Vector& point) override;
};
}
