#pragma once

#include "Common.h"

namespace Functions
{
class InterpolationSplineBase
{
public:
   InterpolationSplineBase(const Vector& arguments, const Vector& parameters);
   std::pair<size_t, size_t> FindIntervalOfArgument(double argument);

   double GetArgument(size_t index) const;
   double GetValue(size_t index) const;

protected:
   Vector m_arguments;
   Vector m_values;
};
}
