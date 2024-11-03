#pragma once

#include "IFunction.h"
#include "LineFunctionBase.h"

namespace Functions
{
class LineFunction : public IDifferentiableFunction, public LineFunctionBase
{
public:
   LineFunction(const Vector& parameters);
   Vector Gradient(const Vector& point) override;
   double Value(const Vector& point) override;
};
}




