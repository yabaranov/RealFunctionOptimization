#pragma once
#include "IOptimizatorBuilder.h"

namespace Optimizators
{

class GaussNewtonOptimizator;

class GaussNewtonOptimizatorBuilder : public IOptimizatorBuilder
{
public:
    GaussNewtonOptimizatorBuilder();

    GaussNewtonOptimizatorBuilder& SetFunctional(std::unique_ptr<Functionals::IFunctional> functional) override;
    GaussNewtonOptimizatorBuilder& SetFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory) override;
    GaussNewtonOptimizatorBuilder& SetMaxIterations(uint32_t maxIterations) override;
    GaussNewtonOptimizatorBuilder& SetMaxResidual(double maxResidual) override;
    std::unique_ptr<IOptimizator> Build() override;
    void Reset() override;

    ~GaussNewtonOptimizatorBuilder() override = default;

private:
    std::unique_ptr<GaussNewtonOptimizator> m_gaussNewtonOptimizator;
};
}