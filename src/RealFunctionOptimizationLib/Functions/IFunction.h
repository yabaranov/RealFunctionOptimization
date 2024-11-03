#pragma once

#include "Common.h"

namespace Functions
{
class IFunction
{
public:
   virtual ~IFunction() = default;
   virtual double Value(const Vector& point) = 0;
};

class IDifferentiableFunction : public IFunction
{
public:
   virtual ~IDifferentiableFunction() = default;
   virtual Vector Gradient(const Vector& point) = 0;
};
}
