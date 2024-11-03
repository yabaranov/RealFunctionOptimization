#pragma once

#include <memory>

namespace Functionals
{
class IFunctional;
}

namespace Functions
{
class IFunctionFactory;
}

namespace Optimizators
{
class IOptimizator;

class IOptimizatorBuilder
{
public:
    virtual ~IOptimizatorBuilder() = default;
    virtual IOptimizatorBuilder& setFunctional(std::unique_ptr<Functionals::IFunctional> functional) = 0;
    virtual IOptimizatorBuilder& setFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory) = 0;
    virtual IOptimizatorBuilder& setMaxIterations(uint32_t maxIterations) = 0;
    virtual IOptimizatorBuilder& setMaxResidual(double maxResidual) = 0;
    virtual std::unique_ptr<IOptimizator> getOptimizator() = 0;
    virtual void reset() = 0;
};
}
