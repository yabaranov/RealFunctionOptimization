#include "LineFunction.h"

namespace Functions
{

LineFunction::InternalLineFunction::InternalLineFunction(const Vector& parameters) : LineFunctionBase(parameters)
{
}

Vector LineFunction::InternalLineFunction::Gradient(const Vector& point)
{
   return m_coefficients;
}

double LineFunction::InternalLineFunction::Value(const Vector& point)
{
   if(point.size() != m_coefficients.size())
      throw std::runtime_error("The number of variables does not match the number of parameters");

   return point.dot(m_coefficients) + m_freeMember;
}

std::unique_ptr<IFunction> LineFunction::Bind(const Vector& parameters)
{
   return std::make_unique<InternalLineFunction>(parameters);
}

}
