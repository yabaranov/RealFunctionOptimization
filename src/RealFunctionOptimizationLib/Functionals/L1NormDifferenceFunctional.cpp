#include "L1NormDifferenceFunctional.h"

#include "Functions/IFunction.h"

namespace Functionals
{
using namespace Functions;

L1NormDifferenceFunctional::L1NormDifferenceFunctional(const std::vector<FunctionPointAndValue>& functionValueTable)
   : FunctionalBase(functionValueTable)
{
}

double L1NormDifferenceFunctional::Value(IFunction& function)
{
   auto sum = 0.0;

   for(const auto& functionPointAndValue: m_functionValueTable)
   {
      auto difference = function.Value(functionPointAndValue.point) - functionPointAndValue.value;
      sum += std::abs(difference);
   }

   return sum;
}

Vector L1NormDifferenceFunctional::Gradient(IFunction& function)
{
   Vector gradient = Vector::Zero(m_functionValueTable.size());

   if(dynamic_cast<IDifferentiableFunction*>(&function) == nullptr)
       throw std::runtime_error("Gradient accepts only IDifferentiableFunction objective functions");

   auto& differentiableFunction = dynamic_cast<IDifferentiableFunction&>(function);

   for (const auto& functionPointAndValue : m_functionValueTable)
   {
      Vector functionGradient = differentiableFunction.Gradient(functionPointAndValue.point);

      auto difference = function.Value(functionPointAndValue.point) - functionPointAndValue.value;
      gradient += difference > 0 ? functionGradient : -functionGradient;
   }

   return gradient;
}

}
