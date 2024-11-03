#pragma once

#include "IFunctional.h"

namespace Functionals
{
class L2NormDifferenceFunctional : public IDifferentiableFunctional, public ILeastSquaresFunctional, public FunctionalBase
{
public:
   L2NormDifferenceFunctional(const std::vector<FunctionPointAndValue>& functionValueTable);
   double Value(Functions::IFunction& function) override;
   Vector Gradient(Functions::IDifferentiableFunction& function) override;
   Vector Residual(Functions::IDifferentiableFunction& function) override;
   Matrix Jacobian(Functions::IDifferentiableFunction& function) override;
};
}
