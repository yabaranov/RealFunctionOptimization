#pragma once

#include "IFunction.h"
#include "LineFunctionBase.h"

namespace Functions
{
class LineFunction : public IParametricFunction
{
public:
   LineFunction() = default;
   std::unique_ptr<IFunction> Bind(const Vector& parameters) override;

private:
   class InternalLineFunction : public IDifferentiableFunction, public LineFunctionBase
   {
   public:
      InternalLineFunction(const Vector& parameters);
      Vector Gradient(const Vector& point) override;
      double Value(const Vector& point) override;
   };
};
}




