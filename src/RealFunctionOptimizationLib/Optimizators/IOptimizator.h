#pragma once

#include "Common.h"

class IFunctional;
class IParametricFunction;

class IOptimizator
{
public:
    virtual ~IOptimizator() = default;
    virtual Vector Minimize(IFunctional& objective, IParametricFunction& function, const Vector& initialParameters,
        Vector* minimumParameters = nullptr, Vector* maximumParameters = nullptr) = 0;
};

class OptimizatorBase
{
public:
    OptimizatorBase(uint32_t maxIterations, double maxResidual)
        : m_MaxIterations(maxIterations), m_MaxResidual(maxResidual)
    {}
protected:
    uint32_t m_MaxIterations{0};
    double m_MaxResidual{0.0f};
};