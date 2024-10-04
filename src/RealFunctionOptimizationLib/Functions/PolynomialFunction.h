#pragma once

#include "IFunction.h"
#include "LineFunctionBase.h"

namespace Functions
{
class PolynomialFunction : public IParametricFunction
{
public:
   PolynomialFunction() = default;
   std::unique_ptr<IFunction> Bind(const Vector& parameters) override;

private:
   class InternalPolynomialFunction : public IFunction, public LineFunctionBase
   {
   public:
      InternalPolynomialFunction(const Vector& parameters);
      double Value(const Vector& point) override;
   };
};
}
