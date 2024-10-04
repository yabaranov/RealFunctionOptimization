#pragma once
#include "Common.h"

namespace Functions
{
class LineFunctionBase
{
public:
   LineFunctionBase(const Vector& parameters);

protected:
   Vector m_coefficients;
   double m_freeMember;
};
}
