#include "InterpolationCubicSpline.h"

namespace Functions
{

InterpolationCubicSpline::InternalInterpolationCubicSpline::InternalInterpolationCubicSpline(const Vector& parameters) : InterpolationSplineBase(parameters)
{
   if(parameters.size() < 4)
      throw std::runtime_error("The number of parameters of the interpolation cubic spline must be greater than or equal to 4");
}

double InterpolationCubicSpline::InternalInterpolationCubicSpline::getSplineCoefficient(size_t index)
{
   auto splineCoefficient = 0.0;
   auto n = m_arguments.size();

   if(index == 0)
   {
      auto lengthCurrentInterval  = m_arguments(1) - m_arguments(0);
      auto lengthNextInterval = m_arguments(2) - m_arguments(1);

      splineCoefficient = -(2 * lengthCurrentInterval + lengthNextInterval) * m_values(0) / lengthCurrentInterval / (lengthCurrentInterval + lengthNextInterval)
                          + (lengthCurrentInterval + lengthNextInterval) * m_values(1) / lengthCurrentInterval / lengthNextInterval
                          - lengthCurrentInterval * m_values(2) / (lengthCurrentInterval + lengthNextInterval) / lengthNextInterval;
   }
   else if (0 < index && index < n - 1)
   {
      auto lengthCurrentInterval  = m_arguments(index) - m_arguments(index - 1);
      auto lengthNextInterval = m_arguments(index + 1) - m_arguments(index);

      splineCoefficient = -lengthNextInterval / lengthCurrentInterval / (lengthCurrentInterval + lengthNextInterval) * m_values(index - 1)
                          + (lengthNextInterval - lengthCurrentInterval) * m_values(index) / lengthCurrentInterval / lengthNextInterval
                          + lengthCurrentInterval * m_values(index + 1) / lengthNextInterval / (lengthCurrentInterval + lengthNextInterval);
   }
   else
   {
      auto lengthCurrentInterval  = m_arguments(n - 2) - m_arguments(n - 3);
      auto lengthNextInterval = m_arguments(n - 1) - m_arguments(n - 2);

      splineCoefficient = lengthNextInterval * m_values(n - 3) / (lengthCurrentInterval + lengthNextInterval) / lengthCurrentInterval
                          - (lengthCurrentInterval + lengthNextInterval) * m_values(n - 2) / lengthNextInterval / lengthCurrentInterval
                          + (2 * lengthNextInterval + lengthCurrentInterval) * m_values(n - 1) / lengthNextInterval / (lengthCurrentInterval + lengthNextInterval);
   }

   return splineCoefficient;
}

double InterpolationCubicSpline::InternalInterpolationCubicSpline::Value(const Vector& point)
{
   if(point.size() != 1)
      throw std::runtime_error("The polynomial can only be calculated at one point");

   auto argument = point[0];

   auto intervalOfArguments = FindIntervalOfArguments(argument);
   auto Index1 = intervalOfArguments.first;
   auto Index2 = intervalOfArguments.second;

   auto lengthInterval = m_arguments(Index2) - m_arguments(Index1);
   auto t = (argument - m_arguments(Index1)) / lengthInterval;

   static std::vector<std::function<double(double, double)>> basisFunctions =
   {
      [](double x, double) {return 1 - 3 * x * x + 2 * x * x * x; },
      [](double x, double h) {return h * (x - 2 * x * x + x * x * x); },
      [](double x, double) {return 3 * x * x - 2 * x * x * x; },
      [](double x, double h) {return h * (-x * x + x * x * x); },
   };

   Vector basisFunctionValues;
   for(auto& basisFunction: basisFunctions)
      basisFunctionValues << basisFunction(t, lengthInterval);

   Vector weights;
   weights << m_values(Index1), getSplineCoefficient(Index1), m_values(Index2), getSplineCoefficient(Index2);

   return weights.dot(basisFunctionValues);
}

std::unique_ptr<IFunction> InterpolationCubicSpline::Bind(const Vector& parameters)
{
   return std::make_unique<InternalInterpolationCubicSpline>(parameters);
}

}
