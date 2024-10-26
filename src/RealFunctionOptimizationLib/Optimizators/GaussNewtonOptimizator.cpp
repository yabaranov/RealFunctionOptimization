#include "GaussNewtonOptimizator.h"

#include "Functionals/IFunctional.h"
#include "Functions/IFunction.h"

namespace Optimizators
{
using namespace Functions;
using namespace Functionals;

GaussNewtonOptimizator::GaussNewtonOptimizator(uint32_t maxIterations, double maxResidual)
    : OptimizatorBase(maxIterations, maxResidual)
{
}

Vector GaussNewtonOptimizator::Minimize(IFunctional& objective, IParametricFunction& function,
    const Vector& initialParameters, Vector* minimumParameters, Vector* maximumParameters)
{
    if (dynamic_cast<ILeastSquaresFunctional*>(&objective) == nullptr)
        throw std::runtime_error("GaussNewtonOptimizator accepts only ILeastSquaresFunctional objective functions");

    auto& leastSquaresFunctional = dynamic_cast<ILeastSquaresFunctional&>(objective);

    Vector parameters = initialParameters;

    Vector prevDelta = Vector::Zero(parameters.size());
    for(uint32_t i = 0; i < m_maxIterations; i++)
    {
        Vector residual = leastSquaresFunctional.Residual(*function.Bind(parameters));
        if (residual.norm() < m_maxResidual)
            break;

        Matrix jacobian = leastSquaresFunctional.Jacobian(*function.Bind(parameters));
        Matrix hessian = (jacobian.transpose() * jacobian);

        Vector delta = hessian.colPivHouseholderQr().solve(jacobian.transpose() * residual);
        if ((delta - prevDelta).norm() < 1e-7)
            break;
        prevDelta = delta;

        parameters = parameters - delta;
    }

    return parameters;
}
}
