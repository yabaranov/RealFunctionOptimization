#include <gtest/gtest.h>

#include "Functionals/L1NormDifferenceFunctional.h"

#include "MockFunctions.h"

using testing::AtLeast;
using testing::AtMost;
using testing::Return;
using testing::_;

class L1NormDifferenceFunctionalTests : public testing::Test
{
public:
    std::unique_ptr<Functionals::L1NormDifferenceFunctional> functional;

    const std::vector<Functionals::FunctionPointAndValue> functionValueTable =
        {
            {Vector::Constant(2, 1.0), 1.0},
            {Vector::Constant(2, 2.0), 2.0}
        };

    void SetUp() override
    {
        functional = std::make_unique<Functionals::L1NormDifferenceFunctional>(functionValueTable);
    }
};

TEST_F(L1NormDifferenceFunctionalTests, Value_WithFunction_ShouldReturnValue)
{
    MockFunction mockFunction;

    EXPECT_CALL(mockFunction, Value(functionValueTable[0].point))
        .Times(1)
        .WillOnce(Return(2.0));

    EXPECT_CALL(mockFunction, Value(functionValueTable[1].point))
        .Times(1)
        .WillOnce(Return(1.0));

    ASSERT_EQ(functional->Value(mockFunction), std::abs(2.0 - functionValueTable[0].value) + std::abs(1.0 - functionValueTable[1].value));
}

TEST_F(L1NormDifferenceFunctionalTests, Gradient_WithDifferentiableFunction_ShouldReturnGradient)
{
    MockDifferentiableFunction mockDifferentiableFunction;

    EXPECT_CALL(mockDifferentiableFunction, Value(functionValueTable[0].point))
        .Times(1)
        .WillOnce(Return(2.0));

    EXPECT_CALL(mockDifferentiableFunction, Gradient(functionValueTable[0].point))
        .Times(1)
        .WillOnce(Return(Vector::Constant(2, 1.0)));

    EXPECT_CALL(mockDifferentiableFunction, Value(functionValueTable[1].point))
        .Times(1)
        .WillOnce(Return(1.0));

    EXPECT_CALL(mockDifferentiableFunction, Gradient(functionValueTable[1].point))
        .Times(1)
        .WillOnce(Return(Vector::Constant(2, 1.0)));

    ASSERT_EQ(functional->Gradient(mockDifferentiableFunction), Vector::Zero(2));
}
