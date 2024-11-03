#pragma once

#include "Common.h"

namespace Optimizators
{
class IOptimizator
{
public:
    virtual ~IOptimizator() = default;
    virtual Vector Minimize(const Vector& initialParameters, Vector* minimumParameters = nullptr, Vector* maximumParameters = nullptr) = 0;
};

class OptimizatorBase
{
public:
    OptimizatorBase() = default;
    void setMaxIterations(uint32_t maxIterations) {m_maxIterations = maxIterations;}
    void setMaxResidual(double maxResidual) {m_maxResidual = maxResidual;}

protected:
    uint32_t m_maxIterations{0};
    double m_maxResidual{0.0f};
};
}
