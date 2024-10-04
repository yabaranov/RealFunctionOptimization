#pragma once

#include "IFunction.h"
#include "InterpolationSplineBase.h"

namespace Functions
{
class PiecewiseLineFunction : public IParametricFunction
{
public:
   PiecewiseLineFunction() = default;
   std::unique_ptr<IFunction> Bind(const Vector& parameters) override;

private:
   class InternalPiecewiseLineFunction : public IDifferentiableFunction, public InterpolationSplineBase
   {
   public:
      InternalPiecewiseLineFunction(const Vector& parameters);
      Vector Gradient(const Vector& point) override;
      double Value(const Vector& point) override;
   };
};
}
