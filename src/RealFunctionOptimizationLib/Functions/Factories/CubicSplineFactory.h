#pragma once

#include "IFunctionFactory.h"
#include "Functions/CubicSpline/CubicSpline.h"
#include "Functions/CubicSpline/Impl/Factories/ICubicSplineImplFactory.h"

namespace Functions
{
class CubicSplineFactory : public IFunctionFactory
{
public:
    CubicSplineFactory(std::unique_ptr<ICubicSplineImplFactory> cubicSplineImplFactory) : m_cubicSplineImplFactory(std::move(cubicSplineImplFactory))
    {}

    std::unique_ptr<Functions::IFunction> CreateFunction(const Vector& parameters) const override
    {
        auto impl = m_cubicSplineImplFactory->CreateCubicSplineImpl(parameters);

        return std::make_unique<Functions::CubicSpline>(std::move(impl));
    }

    ~CubicSplineFactory() override = default;

private:
    std::unique_ptr<ICubicSplineImplFactory> m_cubicSplineImplFactory;
};
}
