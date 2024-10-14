#pragma once
#include "Common.h"

namespace Functions
{
    class IFunction;
}

namespace Functionals
{
    class IFunctional
    {
    public:
        virtual ~IFunctional() = default;
        virtual double Value(Functions::IFunction& function);
    };

    class IDifferentiableFunctional : public IFunctional
    {
    public:
        ~IDifferentiableFunctional() override = default;
        virtual Vector Gradient(Functions::IFunction& function);
    };

    class ILeastSquaresFunctional : public IFunctional
    {
    public:
        ~ILeastSquaresFunctional() override = default;
        virtual Vector Residual(Functions::IFunction& function);
        virtual Matrix Jacobian(Functions::IFunction& function);
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
