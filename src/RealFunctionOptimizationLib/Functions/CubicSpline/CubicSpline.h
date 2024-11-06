#pragma once

#include "Functions/IFunction.h"

namespace Functions
{
class CubicSplineImpl;

class CubicSpline : public IFunction
{
public:
    CubicSpline(std::unique_ptr<CubicSplineImpl> impl);
    double Value(const Vector& point) override;

private:
    std::unique_ptr<CubicSplineImpl> m_impl;
};
}
