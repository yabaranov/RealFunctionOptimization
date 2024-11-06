#include "SmoothingCubicSplineImpl.h"

#include <ranges>

namespace Functions
{
SmoothingCubicSplineImpl::SmoothingCubicSplineImpl(const Vector& arguments, const Vector& parameters, const Vector& nodes, std::function<double(double)> alpha)
    : CubicSplineImpl(arguments, parameters), m_nodes(nodes)
{
    auto&& [matrix, rightSide] = BuildSystem(alpha);
    m_splineCoefficients = matrix.completeOrthogonalDecomposition().solve(rightSide);
}

double SmoothingCubicSplineImpl::Value(const Vector& point)
{
    if(point.size() != 1)
        throw std::runtime_error("The cubic spline can only be calculated at 1d point");

    auto argument = point[0];
    auto&& [index1, index2] = FindIntervalOfArgument(m_nodes, argument);

    auto lengthInterval = m_nodes(index2) - m_nodes(index1);
    auto t = (argument - m_nodes(index1)) / lengthInterval;

    Vector basisFunctionValues(m_basisFunctions.size());
    for(auto&& [i, basisFunction]: std::ranges::views::enumerate(m_basisFunctions))
        basisFunctionValues[i] = basisFunction(t, lengthInterval);

    Vector weights(m_basisFunctions.size());
    for(size_t i = 0; i < m_basisFunctions.size(); i++)
        weights[i] = m_splineCoefficients[2 * index1 + i];

    return weights.dot(basisFunctionValues);
}

std::pair<Matrix, Vector> SmoothingCubicSplineImpl::BuildSystem(std::function<double(double)> alpha)
{
    Vector rightSide = Vector::Zero(2 * m_nodes.size());
    Matrix matrix = Matrix::Zero(rightSide.size(), rightSide.size());

    size_t num = 0;
    for (size_t k = 0; k < m_nodes.size() - 1; k++)
    {
        auto h = m_nodes[k + 1] - m_nodes[k];
        while (num < m_arguments.size() && m_arguments[num] < m_nodes[k + 1] && m_arguments[num] >= m_nodes[k])
        {
            auto t = (m_arguments[num] - m_nodes[k]) / h;
            for(size_t i = 0; i < m_basisFunctions.size(); i++)
            {
                auto val = m_basisFunctions[i](t, h);
                for(size_t j = 0; j < m_basisFunctions.size(); j++)
                    matrix(2 * k + i, 2 * k + j) += val * m_basisFunctions[j](t, h);
                rightSide[2 * k + i] += val * m_values[num];
            }
            num++;
        }

        static std::vector<std::function<double(double, double)>> derivativesOfBasisFunctions =
        {
            [](double x, double h) { return (-6 * x + 6 * x * x) / h; },
            [](double x, double)   { return 1 - 4 * x + 3 * x * x; },
            [](double x, double h) { return (6 * x - 6 * x * x) / h; },
            [](double x, double)   { return -2 - x + 3 * x * x; },
        };

        for(size_t i = 0; i < m_basisFunctions.size(); i++)
            for(size_t j = 0; j < m_basisFunctions.size(); j++)
                matrix(2 * k + i, 2 * k + j) += SimpsonIntegral([&](double x){ return alpha(x) * derivativesOfBasisFunctions[i](x, h) * derivativesOfBasisFunctions[j](x, h); },
                                                                SimpsonIntegralParameters{.a = 0.0, .b = 1.0, .numberOfSteps = 100});
    }

    return {matrix, rightSide};
}

double SmoothingCubicSplineImpl::SimpsonIntegral(std::function<double(double)> function, const SimpsonIntegralParameters& settigs)
{
    auto a = settigs.a;
    auto b = settigs.b;
    auto numberOfSteps = settigs.numberOfSteps;

    auto step = (b - a) / numberOfSteps;
    auto sumOfIntegrals = 0.0;

    auto startOfInterval = a + 0 * step;
    for (size_t i = 0; i < numberOfSteps; i++)
    {
        auto endOfInterval = a + (i + 1) * step;
        sumOfIntegrals += step * (function(startOfInterval) + 4.0 * function((startOfInterval + endOfInterval) / 2.0) + function(endOfInterval)) / 6.0;
        startOfInterval = endOfInterval;
    }

    return sumOfIntegrals;
}
}
