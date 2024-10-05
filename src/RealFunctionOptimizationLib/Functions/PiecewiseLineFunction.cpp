#include "PiecewiseLineFunction.h"
namespace Functions
{

PiecewiseLineFunction::InternalPiecewiseLineFunction::InternalPiecewiseLineFunction(const Vector& parameters) : InterpolationSplineBase(parameters)
{
   if(parameters.size() < 2)
      throw std::runtime_error("The number of parameters of the piecewise line function must be greater than or equal to 2");
}

Vector PiecewiseLineFunction::InternalPiecewiseLineFunction::Gradient(const Vector& point)
{
   if(point.size() != 1)
      throw std::runtime_error("The piecewise line function gradient can only be calculated at 1d point");

   auto argument = point[0];
   auto&& [index1, index2] = FindIntervalOfArguments(argument);

   Vector gradient;
   gradient << (m_values(index2) - m_values(index1)) / (m_arguments(index2) - m_arguments(index1));

   return gradient;
}

double PiecewiseLineFunction::InternalPiecewiseLineFunction::Value(const Vector& point)
{
   if(point.size() != 1)
      throw std::runtime_error("The piecewise line function can only be calculated at 1d point");

   auto argument = point[0];
   auto&& [index1, index2] = FindIntervalOfArguments(argument);

   return m_values(index1) +
          (argument - m_arguments(index1)) * (m_values(index2) - m_values(index1)) / (m_arguments(index2) - m_arguments(index1));
}

std::unique_ptr<IFunction> PiecewiseLineFunction::Bind(const Vector& parameters)
{
   return std::make_unique<InternalPiecewiseLineFunction>(parameters);
}

}
