#include "GaussNewtonOptimizatorBuilder.h"

#include "Optimizators/IOptimizator.h"
#include "Optimizators/GaussNewtonOptimizator.h"

#include "Functionals/IFunctional.h"
#include "Functions/Factories/IDifferentiableFunctionFactory.h"

#include "Functionals/IFunctional.h"

namespace Optimizators
{
GaussNewtonOptimizatorBuilder::GaussNewtonOptimizatorBuilder()
{
    reset();
}

IOptimizatorBuilder& GaussNewtonOptimizatorBuilder::setFunctional(std::unique_ptr<Functionals::IFunctional> functional)
{
    auto differentiableFunctional = dynamic_cast<Functionals::ILeastSquaresFunctional*>(functional.get());
    if (differentiableFunctional == nullptr)
        throw std::runtime_error("GradientDescentOptimizator accepts only ILeastSquaresFunctional");

    m_gaussNewtonOptimizator->setFunctional(std::unique_ptr<Functionals::ILeastSquaresFunctional>(differentiableFunctional));
    functional.release();
    return *this;
}

IOptimizatorBuilder& GaussNewtonOptimizatorBuilder::setFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory)
{
    auto differentiablefunctionFactory = dynamic_cast<Functions::IDifferentiableFunctionFactory*>(functionFactory.get());
    if (differentiablefunctionFactory == nullptr)
        throw std::runtime_error("GradientDescentOptimizator accepts only IDifferentiableFunctionFactory");

    m_gaussNewtonOptimizator->setFunctionFactory(std::unique_ptr<Functions::IDifferentiableFunctionFactory>(differentiablefunctionFactory));
    return *this;
}

IOptimizatorBuilder& GaussNewtonOptimizatorBuilder::setMaxIterations(uint32_t maxIterations)
{
    m_gaussNewtonOptimizator->setMaxIterations(maxIterations);
    return *this;
}

IOptimizatorBuilder& GaussNewtonOptimizatorBuilder::setMaxResidual(double maxResidual)
{
    m_gaussNewtonOptimizator->setMaxResidual(maxResidual);
    return *this;
}

std::unique_ptr<IOptimizator> GaussNewtonOptimizatorBuilder::getOptimizator()
{
    auto optimizator = std::move(m_gaussNewtonOptimizator);
    reset();
    return optimizator;
}

void GaussNewtonOptimizatorBuilder::reset()
{
    m_gaussNewtonOptimizator.reset();
    m_gaussNewtonOptimizator = std::make_unique<GaussNewtonOptimizator>();
}
}
