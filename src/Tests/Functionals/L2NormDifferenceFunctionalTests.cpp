#include <gtest/gtest.h>

#include "Functionals/L2NormDifferenceFunctional.h"

#include "MockFunctions.h"

using testing::AtLeast;
using testing::AtMost;
using testing::Return;
using testing::_;

class L2NormDifferenceFunctionalTests : public testing::Test
{
public:
    std::unique_ptr<Functionals::L2NormDifferenceFunctional> functional;

    const std::vector<Functionals::FunctionPointAndValue> functionValueTable =
        {
            {Vector::Constant(2, 1.0), 1.0},
            {Vector::Constant(2, 2.0), 2.0}
        };

    void SetUp() override
    {
        functional = std::make_unique<Functionals::L2NormDifferenceFunctional>(functionValueTable);
    }
};

TEST_F(L2NormDifferenceFunctionalTests, Value_WithFunction_ShouldReturnValue)
{
    MockFunction mockFunction;

    EXPECT_CALL(mockFunction, Value(functionValueTable[0].point))
        .Times(1)
        .WillOnce(Return(2.0));

    EXPECT_CALL(mockFunction, Value(functionValueTable[1].point))
        .Times(1)
        .WillOnce(Return(4.0));

    auto diff1 = std::abs(2.0 - functionValueTable[0].value);
    auto diff2 = std::abs(4.0 - functionValueTable[1].value);

    ASSERT_EQ(functional->Value(mockFunction), diff1 * diff1 + diff2 * diff2);
}

TEST_F(L2NormDifferenceFunctionalTests, Gradient_WithDifferentiableFunction_ShouldReturnGradient)
{
    MockDifferentiableFunction mockDifferentiableFunction;

    EXPECT_CALL(mockDifferentiableFunction, Value(functionValueTable[0].point))
        .Times(1)
        .WillOnce(Return(2.0));

    auto gradientInPoint1 = Vector::Constant(2, 1.0);
    EXPECT_CALL(mockDifferentiableFunction, Gradient(functionValueTable[0].point))
        .Times(1)
        .WillOnce(Return(gradientInPoint1));

    EXPECT_CALL(mockDifferentiableFunction, Value(functionValueTable[1].point))
        .Times(1)
        .WillOnce(Return(4.0));

    auto gradientInPoint2 = Vector::Constant(2, 2.0);
    EXPECT_CALL(mockDifferentiableFunction, Gradient(functionValueTable[1].point))
        .Times(1)
        .WillOnce(Return(gradientInPoint2));

    auto diff1 = std::abs(2.0 - functionValueTable[0].value);
    auto diff2 = std::abs(4.0 - functionValueTable[1].value);

    ASSERT_EQ(functional->Gradient(mockDifferentiableFunction), 2 * (diff1 * gradientInPoint1 + diff2 * gradientInPoint2));
}

TEST_F(L2NormDifferenceFunctionalTests, Residual_WithFunction_ShouldReturnResidual)
{
    MockDifferentiableFunction mockDifferentiableFunction;

    EXPECT_CALL(mockDifferentiableFunction, Value(functionValueTable[0].point))
        .Times(1)
        .WillOnce(Return(2.0));

    EXPECT_CALL(mockDifferentiableFunction, Value(functionValueTable[1].point))
        .Times(1)
        .WillOnce(Return(4.0));

    auto diff1 = std::abs(2.0 - functionValueTable[0].value);
    auto diff2 = std::abs(4.0 - functionValueTable[1].value);
    auto expectedResidual = Vector{{diff1, diff2}};

    ASSERT_EQ(functional->Residual(mockDifferentiableFunction), expectedResidual);
}

TEST_F(L2NormDifferenceFunctionalTests, Jacobian_WithDifferentiableFunction_ShouldReturnJacobian)
{
    MockDifferentiableFunction mockDifferentiableFunction;

    auto gradientInPoint1 = Vector::Constant(2, 1.0);
    EXPECT_CALL(mockDifferentiableFunction, Gradient(functionValueTable[0].point))
        .Times(1)
        .WillOnce(Return(gradientInPoint1));

    auto gradientInPoint2 = Vector::Constant(2, 2.0);
    EXPECT_CALL(mockDifferentiableFunction, Gradient(functionValueTable[1].point))
        .Times(1)
        .WillOnce(Return(gradientInPoint2));

    auto expectedJacobian = Matrix(2, 2);

    expectedJacobian <<
        gradientInPoint1[0], gradientInPoint1[1],
        gradientInPoint2[0], gradientInPoint2[1];

    ASSERT_EQ(functional->Jacobian(mockDifferentiableFunction), expectedJacobian);
}
