#include <gtest/gtest.h>

#include "Functionals/LInfNormDifferenceFunctional.h"

#include "MockFunctions.h"

using testing::AtLeast;
using testing::AtMost;
using testing::Return;
using testing::_;

class LInfNormDifferenceFunctionalTests : public testing::Test
{
public:
    std::unique_ptr<Functionals::LInfNormDifferenceFunctional> functional;

    const std::vector<Functionals::FunctionPointAndValue> functionValueTable =
        {
            {Vector::Constant(2, 1.0), 1.0},
            {Vector::Constant(2, 2.0), 2.0}
        };

    void SetUp() override
    {
        functional = std::make_unique<Functionals::LInfNormDifferenceFunctional>(functionValueTable);
    }
};

TEST_F(LInfNormDifferenceFunctionalTests, Value_WithFunction_ShouldReturnValue)
{
    MockFunction mockFunction;

    EXPECT_CALL(mockFunction, Value(functionValueTable[0].point))
        .Times(1)
        .WillOnce(Return(2.0));

    EXPECT_CALL(mockFunction, Value(functionValueTable[1].point))
        .Times(1)
        .WillOnce(Return(4.0));

    ASSERT_EQ(functional->Value(mockFunction), std::max(std::abs(2.0 - functionValueTable[0].value), std::abs(4.0 - functionValueTable[1].value)));
}
