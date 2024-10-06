#pragma once

#include "Common.h"

namespace Functionals
{
    class IFunctional;    
}

namespace Functions
{
    class IParametricFunction;
}

namespace Optimizators
{
class IOptimizator
{
public:
    virtual ~IOptimizator() = default;
    virtual Vector Minimize(Functionals::IFunctional& objective, Functions::IParametricFunction& function,
        const Vector& initialParameters, Vector* minimumParameters = nullptr, Vector* maximumParameters = nullptr) = 0;
};

class OptimizatorBase
{
public:
    OptimizatorBase(uint32_t maxIterations, double maxResidual)
        : m_maxIterations(maxIterations), m_maxResidual(maxResidual)
    {}
protected:
    uint32_t m_maxIterations{0};
    double m_maxResidual{0.0f};
};
}
