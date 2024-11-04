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
    Reset();
}

GaussNewtonOptimizatorBuilder& GaussNewtonOptimizatorBuilder::SetFunctional(std::unique_ptr<Functionals::IFunctional> functional)
{
    auto differentiableFunctional = dynamic_cast<Functionals::ILeastSquaresFunctional*>(functional.get());
    if (differentiableFunctional == nullptr)
        throw std::runtime_error("GradientDescentOptimizator accepts only ILeastSquaresFunctional");

    m_gaussNewtonOptimizator->SetFunctional(std::unique_ptr<Functionals::ILeastSquaresFunctional>(differentiableFunctional));
    functional.release();
    return *this;
}

GaussNewtonOptimizatorBuilder& GaussNewtonOptimizatorBuilder::SetFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory)
{
    auto differentiablefunctionFactory = dynamic_cast<Functions::IDifferentiableFunctionFactory*>(functionFactory.get());
    if (differentiablefunctionFactory == nullptr)
        throw std::runtime_error("GradientDescentOptimizator accepts only IDifferentiableFunctionFactory");

    m_gaussNewtonOptimizator->SetFunctionFactory(std::unique_ptr<Functions::IDifferentiableFunctionFactory>(differentiablefunctionFactory));
    functionFactory.release();
    return *this;
}

GaussNewtonOptimizatorBuilder& GaussNewtonOptimizatorBuilder::SetMaxIterations(uint32_t maxIterations)
{
    m_gaussNewtonOptimizator->SetMaxIterations(maxIterations);
    return *this;
}

GaussNewtonOptimizatorBuilder& GaussNewtonOptimizatorBuilder::SetMaxResidual(double maxResidual)
{
    m_gaussNewtonOptimizator->SetMaxResidual(maxResidual);
    return *this;
}

std::unique_ptr<IOptimizator> GaussNewtonOptimizatorBuilder::Build()
{
    auto optimizator = std::move(m_gaussNewtonOptimizator);
    Reset();
    return optimizator;
}

void GaussNewtonOptimizatorBuilder::Reset()
{
    m_gaussNewtonOptimizator = std::make_unique<GaussNewtonOptimizator>();
}
}
