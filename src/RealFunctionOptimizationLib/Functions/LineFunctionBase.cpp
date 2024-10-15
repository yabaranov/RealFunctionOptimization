#include "LineFunctionBase.h"

namespace Functions
{

LineFunctionBase::LineFunctionBase(const Vector& parameters)
{
   if(parameters.size() == 0)
      throw std::runtime_error("The number of parameters of the function must be greater than 0");

   if(parameters.size() > 1)
      m_coefficients = parameters.head(parameters.size() - 1);

   m_freeMember = parameters(parameters.size() - 1);
}

double LineFunctionBase::getFreeMember() const
{
    return m_freeMember;
}

double LineFunctionBase::getCoefficient(size_t index) const
{
    return m_coefficients(index);
}

}
