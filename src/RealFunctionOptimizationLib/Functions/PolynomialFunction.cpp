#include "PolynomialFunction.h"
#include <iostream>

namespace Functions
{

PolynomialFunction::InternalPolynomialFunction::InternalPolynomialFunction(const Vector& parameters) : LineFunctionBase(parameters)
{
}

double PolynomialFunction::InternalPolynomialFunction::Value(const Vector& point)
{
   if(point.size() != 1 && m_coefficients.size())
      throw std::runtime_error("The polynomial can only be calculated at 1d point");

   auto result = 0.0;
   auto k = m_coefficients.size() - 1;

   if(k >= 0)
   {
      result = m_coefficients(k);
      auto argument = point(0);
      
      for(; k > 0; k--)
         result = m_coefficients(k - 1) + result * argument;
     
     result *= argument;
   }

   return result + m_freeMember;
}

std::unique_ptr<IFunction> PolynomialFunction::Bind(const Vector& parameters)
{
   return std::make_unique<InternalPolynomialFunction>(parameters);
}

}
