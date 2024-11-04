#include "GradientDescentOptimizatorBuilder.h"

#include "Optimizators/IOptimizator.h"
#include "Optimizators/GradientDescentOptimizator.h"

#include "Functionals/IFunctional.h"
#include "Functions/Factories/IDifferentiableFunctionFactory.h"

#include "Functionals/IFunctional.h"

namespace Optimizators
{
GradientDescentOptimizatorBuilder::GradientDescentOptimizatorBuilder()
{
    Reset();
}

GradientDescentOptimizatorBuilder& GradientDescentOptimizatorBuilder::SetFunctional(std::unique_ptr<Functionals::IFunctional> functional)
{
    auto differentiableFunctional = dynamic_cast<Functionals::IDifferentiableFunctional*>(functional.get());
    if (differentiableFunctional == nullptr)
        throw std::runtime_error("GradientDescentOptimizator accepts only IDifferentiableFunctional");

    m_gradientDescentOptimizator->SetFunctional(std::unique_ptr<Functionals::IDifferentiableFunctional>(differentiableFunctional));
    functional.release();
    return *this;
}

GradientDescentOptimizatorBuilder& GradientDescentOptimizatorBuilder::SetFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory)
{
    auto differentiablefunctionFactory = dynamic_cast<Functions::IDifferentiableFunctionFactory*>(functionFactory.get());
    if (differentiablefunctionFactory == nullptr)
        throw std::runtime_error("GradientDescentOptimizator accepts only IDifferentiableFunctionFactory");

    m_gradientDescentOptimizator->SetFunctionFactory(std::unique_ptr<Functions::IDifferentiableFunctionFactory>(differentiablefunctionFactory));
    functionFactory.release();
    return *this;
}

GradientDescentOptimizatorBuilder& GradientDescentOptimizatorBuilder::SetMaxIterations(uint32_t maxIterations)
{
    m_gradientDescentOptimizator->SetMaxIterations(maxIterations);
    return *this;
}

GradientDescentOptimizatorBuilder& GradientDescentOptimizatorBuilder::SetMaxResidual(double maxResidual)
{
    m_gradientDescentOptimizator->SetMaxResidual(maxResidual);
    return *this;
}

std::unique_ptr<IOptimizator> GradientDescentOptimizatorBuilder::Build()
{
    auto optimizator = std::move(m_gradientDescentOptimizator);
    Reset();
    return optimizator;
}

void GradientDescentOptimizatorBuilder::Reset()
{
    m_gradientDescentOptimizator = std::make_unique<GradientDescentOptimizator>();
}
}
