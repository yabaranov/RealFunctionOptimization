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
        double Value(Functions::IFunction& function);
    };

    class IDifferentiableFunctional : public IFunctional
    {
    public:
        ~IDifferentiableFunctional() override = default;
        Vector Gradient(Functions::IFunction& function);
    };

    class ILeastSquaresFunctional : public IFunctional
    {
    public:
        ~ILeastSquaresFunctional() override = default;
        Vector Residual(Functions::IFunction& function);
        Matrix Jacobian(Functions::IFunction& function);
    };
}
