#include "InterpolationSplineBase.h"

namespace Functions
{
InterpolationSplineBase::InterpolationSplineBase(const Vector& arguments, const Vector& parameters)
{
   if (arguments.size() != parameters.size())
      throw std::runtime_error("The number of arguments does not match the number of parameters");
   
   if(parameters.size() < 2)
      throw std::runtime_error("The number of parameters of the function must be no less than 2");

   m_arguments = arguments;
   m_values = parameters;
}

std::pair<size_t, size_t> InterpolationSplineBase::FindIntervalOfArgument(double argument)
{
   auto it = std::lower_bound(m_arguments.begin(), m_arguments.end(), argument);
   if(it == m_arguments.end() || it == m_arguments.begin() && argument < *it)
      throw std::runtime_error("The interpolation spline can only be evaluated within its domain");

   if(it == m_arguments.begin())
      it++;

   auto index2 = std::distance(m_arguments.begin(), it);
   auto index1 = index2 - 1;

   return std::pair{index1, index2};
}

double InterpolationSplineBase::GetArgument(size_t index) const
{
    return m_arguments(index);
}

double InterpolationSplineBase::GetValue(size_t index) const
{
    return m_values(index);
}
}
