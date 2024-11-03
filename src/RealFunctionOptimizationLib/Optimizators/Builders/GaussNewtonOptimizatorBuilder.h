#pragma once
#include "IOptimizatorBuilder.h"

namespace Optimizators
{

class GaussNewtonOptimizator;

class GaussNewtonOptimizatorBuilder : public IOptimizatorBuilder
{
public:
    GaussNewtonOptimizatorBuilder();

    IOptimizatorBuilder& setFunctional(std::unique_ptr<Functionals::IFunctional> functional) override;
    IOptimizatorBuilder& setFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory) override;
    IOptimizatorBuilder& setMaxIterations(uint32_t maxIterations) override;
    IOptimizatorBuilder& setMaxResidual(double maxResidual) override;
    std::unique_ptr<IOptimizator> getOptimizator() override;
    void reset() override;

    ~GaussNewtonOptimizatorBuilder() override = default;

private:
    std::unique_ptr<GaussNewtonOptimizator> m_gaussNewtonOptimizator;
};
}
