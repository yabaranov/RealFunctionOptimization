#pragma once

#include "ICubicSplineImplFactory.h"
#include "Functions/CubicSpline/Impl/InterpolationCubicSplineImpl.h"

namespace Functions
{
class InterpolationCubicSplineImplFactory : public ICubicSplineImplFactory
{

public:
    InterpolationCubicSplineImplFactory(const Vector& arguments)
        : m_arguments(arguments)
    {}

    std::unique_ptr<CubicSplineImpl> CreateCubicSplineImpl(const Vector& parameters) override
    {
        return std::make_unique<InterpolationCubicSplineImpl>(m_arguments, parameters);
    }

    ~InterpolationCubicSplineImplFactory() override = default;

private:
    Vector m_arguments;
};
}
