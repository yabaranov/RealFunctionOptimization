#pragma once
#include "IOptimizator.h"

namespace Functionals
{
class ILeastSquaresFunctional;
}

namespace Functions
{
class IDifferentiableFunctionFactory;
}

namespace Optimizators
{
class GaussNewtonOptimizator : public IOptimizator, public OptimizatorBase
{
public:
    GaussNewtonOptimizator() = default;
    Vector Minimize(const Vector& initialParameters, Vector* minimumParameters, Vector* maximumParameters) override;
    void setFunctional(std::unique_ptr<Functionals::ILeastSquaresFunctional> leastSquaresFunctional);
    void setFunctionFactory(std::unique_ptr<Functions::IDifferentiableFunctionFactory> differentiableFunctionFactory);

private:
    std::unique_ptr<Functionals::ILeastSquaresFunctional> m_leastSquaresFunctional;
    std::unique_ptr<Functions::IDifferentiableFunctionFactory> m_differentiableFunctionFactory;
};
}
