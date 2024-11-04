#pragma once

#include <memory>
#include <expected>
#include <string>

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
    virtual IOptimizatorBuilder& SetFunctional(std::unique_ptr<Functionals::IFunctional> functional) = 0;
    virtual IOptimizatorBuilder& SetFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory) = 0;
    virtual IOptimizatorBuilder& SetMaxIterations(uint32_t maxIterations) = 0;
    virtual IOptimizatorBuilder& SetMaxResidual(double maxResidual) = 0;
    virtual std::expected<std::unique_ptr<IOptimizator>, std::string> Build() = 0;
    virtual void Reset() = 0;
};
}
