#pragma once
#include "Common.h"

namespace Functions
{
class LineFunctionBase
{
public:
   LineFunctionBase(const Vector& parameters);

   double GetFreeMember() const;
   double GetCoefficient(size_t index) const;

protected:
   Vector m_coefficients;
   double m_freeMember;
};
}
