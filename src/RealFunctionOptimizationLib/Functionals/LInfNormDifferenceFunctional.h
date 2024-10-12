#pragma once

#include "IFunctional.h"

namespace Functionals
{
class LInfNormDifferenceFunctional : public IFunctional, public FunctionalBase
{
public:
   LInfNormDifferenceFunctional(const std::vector<FunctionPointAndValue>& functionValueTable);
   double Value(Functions::IFunction& function) override;
};
}
