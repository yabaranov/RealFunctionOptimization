#pragma once

#include "IFunction.h"
#include "InterpolationSplineBase.h"

namespace Functions
{
class InterpolationCubicSpline : public IParametricFunction
{
public:
   InterpolationCubicSpline(const Vector& arguments);
   std::unique_ptr<IFunction> Bind(const Vector& parameters) override;

private:
   class InternalInterpolationCubicSpline : public IFunction, public InterpolationSplineBase
   {
   public:
      InternalInterpolationCubicSpline(const Vector& arguments, const Vector& parameters);
      double Value(const Vector& point) override;
   private:
      double GetSplineCoefficient(size_t index);
   };

   Vector m_arguments;
};
}
