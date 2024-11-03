#pragma once
#include "IOptimizatorBuilder.h"

namespace Optimizators
{

class GradientDescentOptimizator;

class GradientDescentOptimizatorBuilder : public IOptimizatorBuilder
{
public:
    GradientDescentOptimizatorBuilder();

    IOptimizatorBuilder& setFunctional(std::unique_ptr<Functionals::IFunctional> functional) override;
    IOptimizatorBuilder& setFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory) override;
    IOptimizatorBuilder& setMaxIterations(uint32_t maxIterations) override;
    IOptimizatorBuilder& setMaxResidual(double maxResidual) override;
    std::unique_ptr<IOptimizator> getOptimizator() override;
    void reset() override;

   ~GradientDescentOptimizatorBuilder() override = default;

private:
    std::unique_ptr<GradientDescentOptimizator> m_gradientDescentOptimizator;
};
}
