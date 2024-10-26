#include "L2NormDifferenceFunctional.h"

#include "Functions/IFunction.h"

#include <ranges>

namespace Functionals
{
using namespace Functions;
namespace views = std::ranges::views;

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

   // IDifferentiableFunction does not include any method for getting the gradient dimensionality,
   // so we have to write this garbage
   Vector gradient = differentiableFunction.Gradient(m_functionValueTable.front().point);
   gradient *= 2 * (function.Value(m_functionValueTable.front().point) - m_functionValueTable.front().value);

   for (const auto& functionPointAndValue : m_functionValueTable | views::drop(1))
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

   // IDifferentiableFunction does not include any method for getting the gradient dimensionality,
   // so we have to write this garbage
   Vector functionGradient = differentiableFunction.Gradient(m_functionValueTable.front().point);
   Matrix jacobian = Matrix::Zero(m_functionValueTable.size(), functionGradient.size());
   jacobian.row(0) = functionGradient;
   
   for (auto&& [index, pointValue] : std::views::enumerate(m_functionValueTable) | views::drop(1))
   {
      functionGradient = differentiableFunction.Gradient(pointValue.point);

      jacobian.row(index) = functionGradient;
   }
   
   return jacobian;
}
}

