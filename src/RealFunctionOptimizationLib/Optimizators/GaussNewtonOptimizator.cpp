#include "GaussNewtonOptimizator.h"

#include "Functionals/IFunctional.h"
#include "Functions/IFunction.h"
#include "Functions/Factories/IDifferentiableFunctionFactory.h"

namespace Optimizators
{
using namespace Functions;
using namespace Functionals;

Vector GaussNewtonOptimizator::Minimize(const Vector& initialParameters, Vector* minimumParameters, Vector* maximumParameters)
{
    Vector parameters = initialParameters;

    Vector prevDelta = Vector::Zero(parameters.size());
    for(uint32_t i = 0; i < m_maxIterations; i++)
    {
        auto temp = m_differentiableFunctionFactory->CreateFunction(parameters);

        auto g = temp->Value(Vector{{5.0}});
        Vector residual = m_leastSquaresFunctional->Residual(dynamic_cast<IDifferentiableFunction&>(*m_differentiableFunctionFactory->CreateFunction(parameters)));
        if (residual.norm() < m_maxResidual)
            break;

        Matrix jacobian = m_leastSquaresFunctional->Jacobian(dynamic_cast<IDifferentiableFunction&>(*m_differentiableFunctionFactory->CreateFunction(parameters)));
        Matrix hessian = (jacobian.transpose() * jacobian);

        Vector delta = hessian.colPivHouseholderQr().solve(jacobian.transpose() * residual);
        if ((delta - prevDelta).norm() < 1e-7)
            break;
        prevDelta = delta;

        parameters = parameters - delta;
    }

    return parameters;
}

void GaussNewtonOptimizator::setFunctional(std::unique_ptr<Functionals::ILeastSquaresFunctional> leastSquaresFunctional)
{
    m_leastSquaresFunctional = std::move(leastSquaresFunctional);
}

void GaussNewtonOptimizator::setFunctionFactory(std::unique_ptr<Functions::IDifferentiableFunctionFactory> differentiableFunctionFactory)
{
    m_differentiableFunctionFactory = std::move(differentiableFunctionFactory);
}
}
