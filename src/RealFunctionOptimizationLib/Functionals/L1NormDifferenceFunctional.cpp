#include "L1NormDifferenceFunctional.h"

#include <ranges>

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

Vector L1NormDifferenceFunctional::Gradient(Functions::IDifferentiableFunction& differentiableFunction)
{
   namespace views = std::ranges::views;
   
   // IDifferentiableFunction does not include any method for getting the gradient dimensionality,
   // so we have to write this garbage
   Vector gradient = differentiableFunction.Gradient(m_functionValueTable.front().point);
   gradient *= (differentiableFunction.Value(m_functionValueTable.front().point) - m_functionValueTable.front().value) > 0 ?
      1.0 : -1.0;

   for (const auto& functionPointAndValue : m_functionValueTable | views::drop(1))
   {
      Vector functionGradient = differentiableFunction.Gradient(functionPointAndValue.point);
      auto difference = differentiableFunction.Value(functionPointAndValue.point) - functionPointAndValue.value;
      gradient += difference > 0 ? functionGradient : -functionGradient;
   }

   return gradient;
}
}
