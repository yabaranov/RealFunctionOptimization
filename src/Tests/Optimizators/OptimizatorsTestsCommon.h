#pragma once

#include <gtest/gtest.h>

#include "Functionals/L1NormDifferenceFunctional.h"
#include "Functionals/L2NormDifferenceFunctional.h"
#include "Functionals/LInfNormDifferenceFunctional.h"

class FunctionalOptimizationTests : public testing::Test
{
public:
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
};

class L1NormOptimizationTests : public FunctionalOptimizationTests
{
public:
    std::unique_ptr<Functionals::L1NormDifferenceFunctional> LineFunctional;
    std::unique_ptr<Functionals::L1NormDifferenceFunctional> SplineFunctional;
    std::unique_ptr<Functionals::L1NormDifferenceFunctional> CubicSplineFunctional;

    void SetUp() override
    {
        LineFunctional = std::make_unique<Functionals::L1NormDifferenceFunctional>(FunctionYIsXTable);
        SplineFunctional = std::make_unique<Functionals::L1NormDifferenceFunctional>(FunctionYIsAbsXTable);
        CubicSplineFunctional = std::make_unique<Functionals::L1NormDifferenceFunctional>(FunctionYIsZigZagXTable);
    }
};

class L2NormOptimizationTests : public FunctionalOptimizationTests
{
public:
    std::unique_ptr<Functionals::L2NormDifferenceFunctional> LineFunctional;
    std::unique_ptr<Functionals::L2NormDifferenceFunctional> SplineFunctional;
    std::unique_ptr<Functionals::L2NormDifferenceFunctional> CubicSplineFunctional;
    
    void SetUp() override
    {
        LineFunctional = std::make_unique<Functionals::L2NormDifferenceFunctional>(FunctionYIsXTable);
        SplineFunctional = std::make_unique<Functionals::L2NormDifferenceFunctional>(FunctionYIsAbsXTable);
        CubicSplineFunctional = std::make_unique<Functionals::L2NormDifferenceFunctional>(FunctionYIsZigZagXTable);
    }
};

class LInfNormOptimizationTests : public FunctionalOptimizationTests
{
public:
    std::unique_ptr<Functionals::LInfNormDifferenceFunctional> LineFunctional;
    std::unique_ptr<Functionals::LInfNormDifferenceFunctional> SplineFunctional;
    std::unique_ptr<Functionals::LInfNormDifferenceFunctional> CubicSplineFunctional;

    void SetUp() override
    {
        LineFunctional = std::make_unique<Functionals::LInfNormDifferenceFunctional>(FunctionYIsXTable);
        SplineFunctional = std::make_unique<Functionals::LInfNormDifferenceFunctional>(FunctionYIsAbsXTable);
        CubicSplineFunctional = std::make_unique<Functionals::LInfNormDifferenceFunctional>(FunctionYIsZigZagXTable);
    }
};
