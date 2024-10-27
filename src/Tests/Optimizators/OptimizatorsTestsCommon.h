#pragma once

#include <gtest/gtest.h>

#include "Functionals/L1NormDifferenceFunctional.h"
#include "Functionals/L2NormDifferenceFunctional.h"
#include "Functionals/LInfNormDifferenceFunctional.h"
#include "Functionals/MonteCarloIntegralFunctional.h"
#include "Functions/IFunction.h"

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


static const Vector INTEGRAL_DOMAIN_MIN = Vector{{0.0}};
static const Vector INTEGRAL_DOMAIN_MAX = Vector{{1.0}};
static const uint32_t INTEGRAL_SAMPLES = 1'000;
static const uint32_t INTEGRAL_SEED = 0;
static const Vector INTEGRAL_PARAMETERS = Vector{{0.0}};

class IntegralFunctionalOptimizationTests : public testing::Test
{
public:
    // function is (x^2 - a)^2, where a is a parameter
    class IntegralFunction : public Functions::IParametricFunction
    {
    public:
        std::unique_ptr<Functions::IFunction> Bind(const Vector& parameters) override
        {
            return std::make_unique<InternalIntegralFunction>(parameters);
        }
    private:
        class InternalIntegralFunction : public Functions::IFunction
        {
        public:
            InternalIntegralFunction(const Vector& parameters) : m_parameters(parameters) {}
            double Value(const Vector& point) override
            {
                double val = point[0] * point[0] - m_parameters[0];
                return val * val;
            }
        private:
            Vector m_parameters;
        };
    };
public:
    uint32_t MaxIterations{100'000};
    double MaxResidual{1e-4};
    std::unique_ptr<Functionals::MonteCarloIntegralFunctional> Functional;
    void SetUp() override
    {
        Functional = std::make_unique<Functionals::MonteCarloIntegralFunctional>(
            Functionals::IntegralHyperBoxDomain{.MinParameters = INTEGRAL_DOMAIN_MIN, .MaxParameters = INTEGRAL_DOMAIN_MAX},
            INTEGRAL_SAMPLES, INTEGRAL_SEED);
    }
    double GetExpectedMin() const
    {
        // https://www.youtube.com/watch?v=2Tz8KzMiVOY  the min of integral_0_1((x^2 - a)^2) is 4/45, with the value of a being 1/3
        return 1.0 / 3.0;
    }
};