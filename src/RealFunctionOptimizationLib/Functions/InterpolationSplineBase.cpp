#include "InterpolationSplineBase.h"
namespace Functions
{

InterpolationSplineBase::InterpolationSplineBase(const Vector& parameters)
{
   if(parameters.size() == 0)
      throw std::runtime_error("The number of parameters of the function must be greater than 0");

   if(parameters.size() % 2 != 0)
      throw std::runtime_error("The number of parameters of the spline function must be even");

   if(parameters.size() < 4)
      throw std::runtime_error("The number of parameters of the spline function must be greater than or equal to 4");

   m_arguments.resize(parameters.size() / 2);
   m_values.resize(parameters.size() / 2);

   for(size_t i = 0; i < parameters.size(); i += 2)
   {
       m_arguments(i / 2) = parameters(i);
       m_values(i / 2) = parameters(i + 1);
   }
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
