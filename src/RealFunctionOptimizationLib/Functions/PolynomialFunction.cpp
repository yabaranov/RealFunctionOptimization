#include "PolynomialFunction.h"

namespace Functions
{
PolynomialFunction::PolynomialFunction(const Vector& parameters) : LineFunctionBase(parameters)
{
}

double PolynomialFunction::Value(const Vector& point)
{
   if(point.size() != 1 && m_coefficients.size())
      throw std::runtime_error("The polynomial can only be calculated at 1d point");

   auto result = 0.0;
   auto numberOfCoefficients = m_coefficients.size();

   if(numberOfCoefficients > 0)
   {
      result = m_coefficients(0);
      auto argument = point(0);
      
      for(size_t i = 1; i < numberOfCoefficients; i++)
         result = m_coefficients(i) + result * argument;
     
     result *= argument;
   }

   return result + m_freeMember;
}
}
