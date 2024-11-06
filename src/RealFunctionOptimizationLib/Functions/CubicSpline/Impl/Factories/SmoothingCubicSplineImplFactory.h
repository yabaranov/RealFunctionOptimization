#pragma once

#include "ICubicSplineImplFactory.h"
#include "Functions/CubicSpline/Impl/SmoothingCubicSplineImpl.h"

namespace Functions
{
class SmoothingCubicSplineImplFactory : public ICubicSplineImplFactory
{

public:
    SmoothingCubicSplineImplFactory(const Vector& arguments, const Vector& nodes, std::function<double(double)> alpha)
        : m_arguments(arguments), m_nodes(nodes), m_alpha(alpha)
    {}

    std::unique_ptr<CubicSplineImpl> CreateCubicSplineImpl(const Vector& parameters) override
    {
        return std::make_unique<SmoothingCubicSplineImpl>(m_arguments, parameters, m_nodes, m_alpha);
    }

    ~SmoothingCubicSplineImplFactory() override = default;

private:
    Vector m_arguments;
    Vector m_nodes;
    std::function<double(double)> m_alpha;
};
}
