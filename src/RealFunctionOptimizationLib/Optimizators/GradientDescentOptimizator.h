#pragma once
#include "IOptimizator.h"

namespace Functionals
{
    class IDifferentiableFunctional;
}

namespace Optimizators
{
class GradientDescentOptimizator : public IOptimizator, public OptimizatorBase
{
public:
    GradientDescentOptimizator(uint32_t maxIterations, double maxResidual);
    Vector Minimize(Functionals::IFunctional& objective, Functions::IParametricFunction& function,
        const Vector& initialParameters, Vector* minimumParameters, Vector* maximumParameters) override;
private:
    double OneDOptimization(Functionals::IDifferentiableFunctional& objective, Functions::IParametricFunction& function,
        const Vector& parameters, const Vector& gradient);
};
}
