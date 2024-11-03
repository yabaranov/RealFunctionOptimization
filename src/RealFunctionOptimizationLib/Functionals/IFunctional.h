#pragma once
#include "Common.h"

namespace Functions
{
    class IFunction;
    class IDifferentiableFunction;
}

namespace Functionals
{
    class IFunctional
    {
    public:
        virtual ~IFunctional() = default;
        virtual double Value(Functions::IFunction& function) = 0;
    };

    class IDifferentiableFunctional : virtual public IFunctional
    {
    public:
        ~IDifferentiableFunctional() override = default;
        virtual Vector Gradient(Functions::IDifferentiableFunction& differentiablefunction) = 0;
    };

    class ILeastSquaresFunctional : virtual public IFunctional
    {
    public:
        ~ILeastSquaresFunctional() override = default;
        virtual Vector Residual(Functions::IDifferentiableFunction& differentiablefunction) = 0;
        virtual Matrix Jacobian(Functions::IDifferentiableFunction& differentiablefunction) = 0;
    };

    struct FunctionPointAndValue
    {
       Vector point;
       double value;
    };

    class FunctionalBase
    {
    public:
       FunctionalBase(const std::vector<FunctionPointAndValue>& functionValueTable) : m_functionValueTable(functionValueTable)
       {}

    protected:
       std::vector<FunctionPointAndValue> m_functionValueTable;
    };
}
