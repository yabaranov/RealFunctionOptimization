#include "InterpolationCubicSplineImpl.h"

#include <ranges>

namespace Functions
{
InterpolationCubicSplineImpl::InterpolationCubicSplineImpl(const Vector& arguments, const Vector& parameters)
    : CubicSplineImpl(arguments, parameters)
{}

double InterpolationCubicSplineImpl::Value(const Vector& point)
{
    if(point.size() != 1)
        throw std::runtime_error("The cubic spline can only be calculated at 1d point");

    auto argument = point[0];
    auto&& [index1, index2] = FindIntervalOfArgument(m_arguments, argument);

    auto lengthInterval = m_arguments(index2) - m_arguments(index1);
    auto t = (argument - m_arguments(index1)) / lengthInterval;

    Vector basisFunctionValues(m_basisFunctions.size());
    for(auto&& [i, basisFunction]: std::ranges::views::enumerate(m_basisFunctions))
        basisFunctionValues[i] = basisFunction(t, lengthInterval);

    Vector weights(m_basisFunctions.size());
    weights << m_values(index1), GetSplineCoefficient(index1), m_values(index2), GetSplineCoefficient(index2);

    return weights.dot(basisFunctionValues);
}

double InterpolationCubicSplineImpl::GetSplineCoefficient(size_t index)
{
    auto splineCoefficient = 0.0;
    auto n = m_arguments.size();

    if(index == 0)
    {
        auto lengthCurrentInterval  = m_arguments(1) - m_arguments(0);
        auto lengthNextInterval = m_arguments(2) - m_arguments(1);

        splineCoefficient = -(2 * lengthCurrentInterval + lengthNextInterval) * m_values(0) / lengthCurrentInterval / (lengthCurrentInterval + lengthNextInterval)
                            + (lengthCurrentInterval + lengthNextInterval) * m_values(1) / lengthCurrentInterval / lengthNextInterval
                            - lengthCurrentInterval * m_values(2) / (lengthCurrentInterval + lengthNextInterval) / lengthNextInterval;
    }
    else if (0 < index && index < n - 1)
    {
        auto lengthCurrentInterval  = m_arguments(index) - m_arguments(index - 1);
        auto lengthNextInterval = m_arguments(index + 1) - m_arguments(index);

        splineCoefficient = -lengthNextInterval / lengthCurrentInterval / (lengthCurrentInterval + lengthNextInterval) * m_values(index - 1)
                            + (lengthNextInterval - lengthCurrentInterval) * m_values(index) / lengthCurrentInterval / lengthNextInterval
                            + lengthCurrentInterval * m_values(index + 1) / lengthNextInterval / (lengthCurrentInterval + lengthNextInterval);
    }
    else
    {
        auto lengthCurrentInterval  = m_arguments(n - 2) - m_arguments(n - 3);
        auto lengthNextInterval = m_arguments(n - 1) - m_arguments(n - 2);

        splineCoefficient = lengthNextInterval * m_values(n - 3) / (lengthCurrentInterval + lengthNextInterval) / lengthCurrentInterval
                            - (lengthCurrentInterval + lengthNextInterval) * m_values(n - 2) / lengthNextInterval / lengthCurrentInterval
                            + (2 * lengthNextInterval + lengthCurrentInterval) * m_values(n - 1) / lengthNextInterval / (lengthCurrentInterval + lengthNextInterval);
    }

    return splineCoefficient;
}
}