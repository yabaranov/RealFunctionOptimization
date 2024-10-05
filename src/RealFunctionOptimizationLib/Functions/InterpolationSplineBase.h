#pragma once

#include "Common.h"
namespace Functions
{

class InterpolationSplineBase
{
public:
   InterpolationSplineBase(const Vector& parameters);
   std::pair<size_t, size_t> FindIntervalOfArguments(double argument);

protected:
   Vector m_arguments;
   Vector m_values;
};

}
