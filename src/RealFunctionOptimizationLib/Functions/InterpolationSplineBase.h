#pragma once

#include "Common.h"
namespace Functions
{

class InterpolationSplineBase
{
public:
   InterpolationSplineBase(const Vector& parameters);
   std::pair<size_t, size_t> FindIntervalOfArguments(double argument);

   double getArgument(size_t index) const;
   double getValue(size_t index) const;

protected:
   Vector m_arguments;
   Vector m_values;
};

}
