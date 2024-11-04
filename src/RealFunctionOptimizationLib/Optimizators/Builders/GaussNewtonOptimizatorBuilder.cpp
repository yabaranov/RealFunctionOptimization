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
    if (differentiableFunctional)
    {
        m_gaussNewtonOptimizator->SetFunctional(std::unique_ptr<Functionals::ILeastSquaresFunctional>(differentiableFunctional));
        functional.release();
    }
    else
        m_errorMessage += "GaussNewtonOptimizator accepts only ILeastSquaresFunctional ";

    return *this;
}

GaussNewtonOptimizatorBuilder& GaussNewtonOptimizatorBuilder::SetFunctionFactory(std::unique_ptr<Functions::IFunctionFactory> functionFactory)
{
    auto differentiablefunctionFactory = dynamic_cast<Functions::IDifferentiableFunctionFactory*>(functionFactory.get());
    if (differentiablefunctionFactory)
    {
        m_gaussNewtonOptimizator->SetFunctionFactory(std::unique_ptr<Functions::IDifferentiableFunctionFactory>(differentiablefunctionFactory));
        functionFactory.release();
    }
    else
        m_errorMessage += "GradientDescentOptimizator accepts only IDifferentiableFunctionFactory ";

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

std::expected<std::unique_ptr<IOptimizator>, std::string> GaussNewtonOptimizatorBuilder::Build()
{
    if (!m_errorMessage.empty())
        return std::unexpected(m_errorMessage);

    auto optimizator = std::move(m_gaussNewtonOptimizator);
    Reset();
    return optimizator;
}

void GaussNewtonOptimizatorBuilder::Reset()
{
    m_errorMessage.clear();
    m_gaussNewtonOptimizator = std::make_unique<GaussNewtonOptimizator>();
}
}
