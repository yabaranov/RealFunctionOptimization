#pragma once
#include "IOptimizatorBuilder.h"

namespace Optimizators
{

class GradientDescentOptimizator;

class GradientDescentOptimizatorBuilder : public IOptimizatorBuilder
{
public:
    GradientDescentOptimizatorBuilder();

    GradientDescentOptimizatorBuilder& SetFunctional(std::unique_ptr<Functionals::IFunctional> functional) override;
    GradientDescentOptimizatorBuilder& SetFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory) override;
    GradientDescentOptimizatorBuilder& SetMaxIterations(uint32_t maxIterations) override;
    GradientDescentOptimizatorBuilder& SetMaxResidual(double maxResidual) override;
    std::unique_ptr<IOptimizator> Build() override;
    void Reset() override;

   ~GradientDescentOptimizatorBuilder() override = default;

private:
    std::unique_ptr<GradientDescentOptimizator> m_gradientDescentOptimizator;
};
}
