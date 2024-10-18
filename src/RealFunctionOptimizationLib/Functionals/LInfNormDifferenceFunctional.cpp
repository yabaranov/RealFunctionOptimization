#include "LInfNormDifferenceFunctional.h"

#include "Functions/IFunction.h"

namespace Functionals
{
using namespace Functions;

LInfNormDifferenceFunctional::LInfNormDifferenceFunctional(const std::vector<FunctionPointAndValue>& functionValueTable)
   : FunctionalBase(functionValueTable)
{
}

double LInfNormDifferenceFunctional::Value(IFunction& function)
{
   auto max = 0.0;

   for(const auto& functionPointAndValue: m_functionValueTable)
   {
      auto difference = function.Value(functionPointAndValue.point) - functionPointAndValue.value;
      max = std::max(std::abs(difference), max);
   }

   return max;
}
}
