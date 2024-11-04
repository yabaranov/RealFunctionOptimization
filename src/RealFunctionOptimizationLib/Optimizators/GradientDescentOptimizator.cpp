#include "GradientDescentOptimizator.h"

#include "Functionals/IFunctional.h"
#include "Functions/IFunction.h"
#include "Functions/Factories/IDifferentiableFunctionFactory.h"

namespace Optimizators
{
using namespace Functions;
using namespace Functionals;

Vector GradientDescentOptimizator::Minimize(const Vector& initialParameters, Vector* minimumParameters, Vector* maximumParameters)
{
    Vector parameters = initialParameters;
    Vector gradient = m_differentiableFunctional->Gradient(dynamic_cast<IDifferentiableFunction&>(*m_differentiableFunctionFactory->CreateFunction(parameters)));

    for (uint32_t i = 0; i < m_maxIterations; i++)
    {
        const double value = m_differentiableFunctional->Value(*m_differentiableFunctionFactory->CreateFunction(parameters));
        if (value < m_maxResidual)
            break;

        const double alpha = OneDOptimization(*m_differentiableFunctional, *m_differentiableFunctionFactory, parameters, gradient);
    
        parameters = parameters - alpha * gradient;
        gradient = m_differentiableFunctional->Gradient(dynamic_cast<IDifferentiableFunction&>(*m_differentiableFunctionFactory->CreateFunction(parameters)));
    }

    return parameters;
}

void GradientDescentOptimizator::SetFunctional(std::unique_ptr<Functionals::IDifferentiableFunctional> differentiableFunctional)
{
    m_differentiableFunctional = std::move(differentiableFunctional);
}

void GradientDescentOptimizator::SetFunctionFactory(std::unique_ptr<Functions::IDifferentiableFunctionFactory> differentiableFunctionFactory)
{
    m_differentiableFunctionFactory = std::move(differentiableFunctionFactory);
}

double GradientDescentOptimizator::OneDOptimization(IDifferentiableFunctional& differentiableFunctional,
    Functions::IDifferentiableFunctionFactory& differentiablefunctionFactory, const Vector& parameters, const Vector& gradient)
{
    static const double GOLDEN_A = (3.0 - std::sqrt(5.0)) / 2.0;
    static const double GOLDEN_B = (std::sqrt(5.0) - 1.0) / 2.0;
    auto fun = [&](double t) { return differentiableFunctional.Value(*differentiablefunctionFactory.CreateFunction(parameters - gradient * t)); };
    
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
