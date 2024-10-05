#include "InterpolationSplineBase.h"
namespace Functions
{

InterpolationSplineBase::InterpolationSplineBase(const Vector& parameters)
{
   if(parameters.size() == 0)
      throw std::runtime_error("The number of parameters of the function must be greater than 0");

   if(parameters.size() % 2 != 0)
      throw std::runtime_error("The number of parameters of the spline function must be even");

   for(size_t i = 0; i < parameters.size(); i += 2)
   {
      m_arguments << parameters(i);
      m_values << parameters(i + 1);
   }
}

std::pair<size_t, size_t> InterpolationSplineBase::FindIntervalOfArguments(double argument)
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

}
