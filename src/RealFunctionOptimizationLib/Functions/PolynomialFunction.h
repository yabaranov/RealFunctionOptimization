#pragma once

#include "IFunction.h"
#include "LineFunctionBase.h"

namespace Functions
{
class PolynomialFunction : public IFunction, public LineFunctionBase
{
public:
   PolynomialFunction(const Vector& parameters);
   double Value(const Vector& point) override;
};
}
