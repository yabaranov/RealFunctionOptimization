#include "PolynomialFunction.h"

namespace Functions
{

PolynomialFunction::InternalPolynomialFunction::InternalPolynomialFunction(const Vector& parameters) : LineFunctionBase(parameters)
{
}

double PolynomialFunction::InternalPolynomialFunction::Value(const Vector& point)
{
   if(point.size() != 1)
      throw std::runtime_error("The polynomial can only be calculated at 1d point");

   auto argument = point[0];

   auto result = 0.0;
   auto k = m_coefficients.size() - 1;

   if(k >= 0)
   {
      result = m_coefficients(k);

      for(; k > 0; k++)
         result = m_coefficients(k - 1) + result * argument;
   }

   return result * argument + m_freeMember;
}

std::unique_ptr<IFunction> PolynomialFunction::Bind(const Vector& parameters)
{
   return std::make_unique<InternalPolynomialFunction>(parameters);
}

}
