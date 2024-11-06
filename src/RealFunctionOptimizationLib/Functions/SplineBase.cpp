#include "SplineBase.h"

namespace Functions
{
SplineBase::SplineBase(const Vector& arguments, const Vector& parameters)
{
   if (arguments.size() != parameters.size())
      throw std::runtime_error("The number of arguments does not match the number of parameters");
   
   if(parameters.size() < 2)
      throw std::runtime_error("The number of parameters of the function must be no less than 2");

   m_arguments = arguments;
   m_values = parameters;
}

std::pair<size_t, size_t> SplineBase::FindIntervalOfArgument(const Vector& arguments, double argument)
{
   auto it = std::lower_bound(arguments.begin(), arguments.end(), argument);
   if(it == arguments.end() || it == arguments.begin() && argument < *it)
      throw std::runtime_error("The spline can only be evaluated within its domain");

   if(it == arguments.begin())
      it++;

   auto index2 = std::distance(arguments.begin(), it);
   auto index1 = index2 - 1;

   return std::pair{index1, index2};
}

double SplineBase::GetArgument(size_t index) const
{
    return m_arguments(index);
}

double SplineBase::GetValue(size_t index) const
{
    return m_values(index);
}
}
