#pragma once

#include "CubicSplineImpl.h"

namespace Functions
{
class SmoothingCubicSplineImpl : public CubicSplineImpl
{
public:
    SmoothingCubicSplineImpl(const Vector& arguments, const Vector& parameters, const Vector& nodes, std::function<double(double)> alpha);
    double Value(const Vector& point) override;

    ~SmoothingCubicSplineImpl() override = default;

private:
    std::pair<Matrix, Vector> BuildSystem(std::function<double(double)> alpha);

    struct SimpsonIntegralParameters
    {
        double a;
        double b;
        size_t numberOfSteps;
    };

    double SimpsonIntegral(std::function<double(double)> function, const SimpsonIntegralParameters& settigs);

    Vector m_nodes;
    Vector m_splineCoefficients;
};
}
