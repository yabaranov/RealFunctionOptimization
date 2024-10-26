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

    Vector parameters = initialParameters;
    Vector gradient = differentiableFunctional.Gradient(*function.Bind(parameters));

    for (uint32_t i = 0; i < m_maxIterations; i++)
    {
        const double value = differentiableFunctional.Value(*function.Bind(parameters));
        if (value < m_maxResidual)
            break;

        const double alpha = OneDOptimization(differentiableFunctional, function, parameters, gradient);
    
        parameters = parameters - alpha * gradient;
        gradient = differentiableFunctional.Gradient(*function.Bind(parameters));
    }

    return parameters;
}

double GradientDescentOptimizator::OneDOptimization(IDifferentiableFunctional& objective,
    IParametricFunction& function, const Vector& parameters, const Vector& gradient)
{
    static const double GOLDEN_A = (3.0 - std::sqrt(5.0)) / 2.0;
    static const double GOLDEN_B = (std::sqrt(5.0) - 1.0) / 2.0;
    auto fun = [&](double t) { return objective.Value(*function.Bind(parameters - gradient * t)); };
    
    double a = 0.0;
    double b = 1.0;
    double length = b - a;
    double x1 = a + GOLDEN_A * length;
    double x2 = a + GOLDEN_B * length;
    double f1 = fun(x1);
    double f2 = fun(x2);

    while (length >= m_maxResidual)
    {
        if (f1 < f2)
        {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = a + GOLDEN_A * (b - a);
            f1 = fun(x1);
        }
        else if (f1 > f2)
        {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = a + GOLDEN_B * (b - a);
            f2 = fun(x2);
        }
        else
        {
            a = x1;
            b = x2;
            x1 = a + GOLDEN_A * (b - a);
            x2 = a + GOLDEN_B * (b - a);
            f1 = fun(x1);
            f2 = fun(x2);
        }
        length = b - a;
    }
    
    return f1 < f2 ? x1 : x2;
}
}
