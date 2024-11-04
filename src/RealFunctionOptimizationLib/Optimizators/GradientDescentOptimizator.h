#pragma once
#include "IOptimizator.h"

namespace Functionals
{
class IDifferentiableFunctional;
}

namespace Functions
{
class IDifferentiableFunctionFactory;
}

namespace Optimizators
{
class GradientDescentOptimizator : public IOptimizator, public OptimizatorBase
{
public:
    GradientDescentOptimizator() = default;
    Vector Minimize(const Vector& initialParameters, Vector* minimumParameters, Vector* maximumParameters) override;
    void SetFunctional(std::unique_ptr<Functionals::IDifferentiableFunctional> differentiableFunctional);
    void SetFunctionFactory(std::unique_ptr<Functions::IDifferentiableFunctionFactory> differentiableFunctionFactory);

private:
    std::unique_ptr<Functionals::IDifferentiableFunctional> m_differentiableFunctional;
    std::unique_ptr<Functions::IDifferentiableFunctionFactory> m_differentiableFunctionFactory;
    double OneDOptimization(Functionals::IDifferentiableFunctional& objective, Functions::IDifferentiableFunctionFactory& differentiablefunctionFactory,
        const Vector& parameters, const Vector& gradient);
};
}
