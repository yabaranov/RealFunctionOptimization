#pragma once

#include "Common.h"
#include <memory>

namespace Functions
{
class CubicSplineImpl;

class ICubicSplineImplFactory
{
public:
    virtual std::unique_ptr<CubicSplineImpl> CreateCubicSplineImpl(const Vector& parameters) = 0;

    virtual ~ICubicSplineImplFactory() = default;
};
}
