#include "CubicSpline.h"
#include "Impl/CubicSplineImpl.h"

namespace Functions
{
CubicSpline::CubicSpline(std::unique_ptr<CubicSplineImpl> impl)
    : m_impl(std::move(impl))
{
}

double CubicSpline::Value(const Vector& point)
{
    return m_impl->Value(point);
}
}
