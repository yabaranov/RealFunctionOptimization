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

    for(uint32_t i = 0; i < m_maxIterations; i++)
    {
        Vector residual = leastSquaresFunctional.Residual(*function.Bind(parameters));
        if (residual.norm() < m_maxResidual)
            break;

        Matrix jacobian = leastSquaresFunctional.Jacobian(*function.Bind(parameters));
        Matrix hessianInverse = (jacobian.transpose() * jacobian).inverse();
        
        parameters = parameters - hessianInverse * jacobian.transpose() * residual;
    }

    return parameters;
}
}
