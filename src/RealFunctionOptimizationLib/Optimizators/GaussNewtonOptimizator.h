#pragma once
#include "IOptimizator.h"

namespace Optimizators
{
class GaussNewtonOptimizator : public IOptimizator, public OptimizatorBase
{
public:
    GaussNewtonOptimizator(uint32_t maxIterations, double maxResidual);
    Vector Minimize(Functionals::IFunctional& objective, Functions::IParametricFunction& function,
        const Vector& initialParameters, Vector* minimumParameters, Vector* maximumParameters) override;
};
}
