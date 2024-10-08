#pragma once

#include "IFunctional.h"
#include "FunctionalBase.h"

namespace Functionals
{

class L1NormDifferenceFunctional : public IDifferentiableFunctional, public FunctionalBase
{
public:
   L1NormDifferenceFunctional(const std::vector<FunctionPointValue>& functionPointValues);
   double Value(Functions::IFunction& function) override;
   Vector Gradient(Functions::IFunction& function) override;
};

}
