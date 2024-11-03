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
    reset();
}

IOptimizatorBuilder& GradientDescentOptimizatorBuilder::setFunctional(std::unique_ptr<Functionals::IFunctional> functional)
{
    auto differentiableFunctional = dynamic_cast<Functionals::IDifferentiableFunctional*>(functional.get());
    if (differentiableFunctional == nullptr)
        throw std::runtime_error("GradientDescentOptimizator accepts only IDifferentiableFunctional");

    m_gradientDescentOptimizator->setFunctional(std::unique_ptr<Functionals::IDifferentiableFunctional>(differentiableFunctional));
    functional.release();
    return *this;
}

IOptimizatorBuilder& GradientDescentOptimizatorBuilder::setFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory)
{
    auto differentiablefunctionFactory = dynamic_cast<Functions::IDifferentiableFunctionFactory*>(functionFactory.get());
    if (differentiablefunctionFactory == nullptr)
        throw std::runtime_error("GradientDescentOptimizator accepts only IDifferentiableFunctionFactory");

    m_gradientDescentOptimizator->setFunctionFactory(std::unique_ptr<Functions::IDifferentiableFunctionFactory>(differentiablefunctionFactory));
    return *this;
}

IOptimizatorBuilder& GradientDescentOptimizatorBuilder::setMaxIterations(uint32_t maxIterations)
{
    m_gradientDescentOptimizator->setMaxIterations(maxIterations);
    return *this;
}

IOptimizatorBuilder& GradientDescentOptimizatorBuilder::setMaxResidual(double maxResidual)
{
    m_gradientDescentOptimizator->setMaxResidual(maxResidual);
    return *this;
}

std::unique_ptr<IOptimizator> GradientDescentOptimizatorBuilder::getOptimizator()
{
    auto optimizator = std::move(m_gradientDescentOptimizator);
    reset();
    return optimizator;
}

void GradientDescentOptimizatorBuilder::reset()
{
    m_gradientDescentOptimizator.reset();
    m_gradientDescentOptimizator = std::make_unique<GradientDescentOptimizator>();
}
}
