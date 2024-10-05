#pragma once

#include "IFunction.h"
#include "InterpolationSplineBase.h"

namespace Functions
{
class InterpolationCubicSpline : public IParametricFunction
{
public:
   InterpolationCubicSpline() = default;
   std::unique_ptr<IFunction> Bind(const Vector& parameters) override;

private:
   class InternalInterpolationCubicSpline : public IFunction, public InterpolationSplineBase
   {
   public:
      InternalInterpolationCubicSpline(const Vector& parameters);
      double Value(const Vector& point) override;
   private:
      double GetSplineCoefficient(size_t index);
   };
};
}
