#include "L2NormDifferenceFunctional.h"

#include "Functions/IFunction.h"

#include <ranges>

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
   if(dynamic_cast<IDifferentiableFunction*>(&function) == nullptr)
      throw std::runtime_error("Gradient accepts only IDifferentiableFunction objective functions");
   auto& differentiableFunction = dynamic_cast<IDifferentiableFunction&>(function);
   
   Vector gradient = Vector::Zero(m_functionValueTable.front().point.size());

   for (const auto& functionPointAndValue : m_functionValueTable)
   {
      Vector functionGradient = differentiableFunction.Gradient(functionPointAndValue.point);

      auto difference = function.Value(functionPointAndValue.point) - functionPointAndValue.value;
      gradient += 2 * difference * functionGradient;
   }

   return gradient;
}

Vector L2NormDifferenceFunctional::Residual(IFunction& function)
{
   Vector residual = Vector::Zero(m_functionValueTable.size());
   for (auto&& [index, pointValue] : std::views::enumerate(m_functionValueTable))
      residual[index] = function.Value(pointValue.point) - pointValue.value;

   return residual;
}

Matrix L2NormDifferenceFunctional::Jacobian(IFunction& function)
{
   if(dynamic_cast<IDifferentiableFunction*>(&function) == nullptr)
      throw std::runtime_error("Gradient accepts only IDifferentiableFunction objective functions");
   auto& differentiableFunction = dynamic_cast<IDifferentiableFunction&>(function);

   Matrix jacobian = Matrix::Zero(m_functionValueTable.size(), m_functionValueTable.front().point.size());
   for (auto&& [index, pointValue] : std::views::enumerate(m_functionValueTable))
   {
      Vector functionGradient = differentiableFunction.Gradient(pointValue.point);

      jacobian.row(index) = functionGradient;
   }
   
   return jacobian;
}
}

