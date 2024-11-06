#pragma once

#include "IFunction.h"
#include "SplineBase.h"

namespace Functions
{
class PiecewiseLineFunction : public IDifferentiableFunction, public SplineBase
{
public:
   PiecewiseLineFunction(const Vector& arguments, const Vector& parameters);
   Vector Gradient(const Vector& point) override;
   double Value(const Vector& point) override;
};
}
