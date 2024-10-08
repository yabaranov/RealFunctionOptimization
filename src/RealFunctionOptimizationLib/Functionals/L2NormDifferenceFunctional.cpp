#include "L2NormDifferenceFunctional.h"

#include "Functions/IFunction.h"

namespace Functionals
{
using namespace Functions;

L2NormDifferenceFunctional::L2NormDifferenceFunctional(const std::vector<FunctionPointAndValue>& functionValueTable)
   : FunctionalBase(functionValueTable)
{
}

double L2NormDifferenceFunctional::Value(IFunction& function)
{
   auto sum = 0.0;

   for(const auto& functionPointAndValue: m_functionValueTable)
   {
      auto difference = function.Value(functionPointAndValue.point) - functionPointAndValue.value;
      sum += difference * difference;
   }

   return sum;
}

Vector L2NormDifferenceFunctional::Gradient(IFunction& function)
{
   Vector gradient = Vector::Zero(m_functionValueTable.size());

   if(dynamic_cast<IDifferentiableFunction*>(&function) == nullptr)
      throw std::runtime_error("Gradient accepts only IDifferentiableFunction objective functions");

   auto& differentiableFunction = dynamic_cast<IDifferentiableFunction&>(function);

   for (const auto& functionPointAndValue : m_functionValueTable)
   {
      Vector functionGradient = differentiableFunction.Gradient(functionPointAndValue.point);

      auto difference = function.Value(functionPointAndValue.point) - functionPointAndValue.value;
      gradient += 2 * difference * functionGradient;
   }

   return gradient;
}

}
