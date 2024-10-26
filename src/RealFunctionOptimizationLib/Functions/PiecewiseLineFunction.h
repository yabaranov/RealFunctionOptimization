#pragma once

#include "IFunction.h"
#include "InterpolationSplineBase.h"

namespace Functions
{
class PiecewiseLineFunction : public IParametricFunction
{
public:
   PiecewiseLineFunction(const Vector& arguments);
   std::unique_ptr<IFunction> Bind(const Vector& parameters) override;

private:
   class InternalPiecewiseLineFunction : public IDifferentiableFunction, public InterpolationSplineBase
   {
   public:
      InternalPiecewiseLineFunction(const Vector& arguments, const Vector& parameters);
      Vector Gradient(const Vector& point) override;
      double Value(const Vector& point) override;
   };

   Vector m_arguments;
};
}
