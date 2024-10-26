#pragma once

#include <gtest/gtest.h>

#include "Functionals/L1NormDifferenceFunctional.h"
#include "Functionals/L2NormDifferenceFunctional.h"
#include "Functionals/LInfNormDifferenceFunctional.h"

static const Vector LINE_INITIAL_PARAMETERS = Vector::Constant(1, 0.5);
static const Vector SPLINE_ARGUMENTS = Vector{{-1.0, 0.0, 1.0}};
static const Vector SPLINE_INITIAL_PARAMETERS = Vector{{1.0, 1.0, 1.0}};
static const Vector CUBIC_SPLINE_ARGUMENTS = Vector{{-1.0, 0.0, 1.0, 2.0}};
static const Vector CUBIC_SPLINE_INITIAL_PARAMETERS = Vector{{0.0, 0.0, 0.0, 0.0}};

template <typename FunctionalNorm>
class FunctionalOptimizationTests : public testing::Test
{
public:
    std::unique_ptr<FunctionalNorm> LineFunctional;
    std::unique_ptr<FunctionalNorm> SplineFunctional;
    std::unique_ptr<FunctionalNorm> CubicSplineFunctional;
    
    uint32_t MaxIterations{100'000};
    double MaxResidual{1e-4};
    // y=x for line function
    const std::vector<Functionals::FunctionPointAndValue> FunctionYIsXTable =
        {
            {Vector::Constant(1, -1.0), -1.0},
            {Vector::Constant(1,  0.0),  0.0},
            {Vector::Constant(1,  1.0),  1.0},
        };
    // y=|x| for line spline
    const std::vector<Functionals::FunctionPointAndValue> FunctionYIsAbsXTable =
        {
            {Vector::Constant(1, -1.0), 1.0},
            {Vector::Constant(1,  0.0), 0.0},
            {Vector::Constant(1,  1.0), 1.0},
        };
    // y=(zigzag of x) for line spline    ->    /\/
    const std::vector<Functionals::FunctionPointAndValue> FunctionYIsZigZagXTable =
        {
            {Vector::Constant(1, -1.0), 0.5},
            {Vector::Constant(1,  0.0), 0.0},
            {Vector::Constant(1,  1.0), 0.5},
            {Vector::Constant(1,  2.0), 0.0},
        };
    double GetMinimizingLineYIsX() const
    {
        // real min is the midpoint
        return FunctionYIsXTable[1].value;
    }

    void SetUp() override
    {
        LineFunctional = std::make_unique<FunctionalNorm>(FunctionYIsXTable);
        SplineFunctional = std::make_unique<FunctionalNorm>(FunctionYIsAbsXTable);
        CubicSplineFunctional = std::make_unique<FunctionalNorm>(FunctionYIsZigZagXTable);
    }
};

using L1NormOptimizationTests = FunctionalOptimizationTests<Functionals::L1NormDifferenceFunctional>;
using L2NormOptimizationTests = FunctionalOptimizationTests<Functionals::L2NormDifferenceFunctional>;
using LInfNormOptimizationTests = FunctionalOptimizationTests<Functionals::LInfNormDifferenceFunctional>;
