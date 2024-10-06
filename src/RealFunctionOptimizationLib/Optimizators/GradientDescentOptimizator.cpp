#include "GradientDescentOptimizator.h"

#include "Functionals/IFunctional.h"
#include "Functions/IFunction.h"

namespace Optimizators
{
using namespace Functions;
using namespace Functionals;

GradientDescentOptimizator::GradientDescentOptimizator(uint32_t maxIterations, double maxResidual)
    : OptimizatorBase(maxIterations, maxResidual)
{
}

Vector GradientDescentOptimizator::Minimize(IFunctional& objective, IParametricFunction& function,
    const Vector& initialParameters, Vector* minimumParameters, Vector* maximumParameters)
{
    if (dynamic_cast<IDifferentiableFunctional*>(&objective) == nullptr)
        throw std::runtime_error("GradientDescentOptimizator accepts only IDifferentiableFunctional objective functions");

    auto& differentiableFunctional = dynamic_cast<IDifferentiableFunctional&>(objective);

    Vector prevParameters;
    prevParameters.resize(initialParameters.size());
    prevParameters.fill(0);
    Vector prevGradient = prevParameters;
    Vector parameters = initialParameters;
    Vector gradient = differentiableFunctional.Gradient(*function.Bind(parameters));

    for (uint32_t i = 0; i < m_maxIterations; i++)
    {
        const double value = differentiableFunctional.Value(*function.Bind(parameters));
        if (value < m_maxResidual)
            break;

        const double gamma = (parameters - prevParameters).dot(gradient - prevGradient) /
            (gradient - prevGradient).norm();
        prevParameters = parameters;
        prevGradient = gradient;
    
        parameters = parameters - gamma * gradient;
        gradient = differentiableFunctional.Gradient(*function.Bind(parameters));
    }

    return parameters;
}
}
