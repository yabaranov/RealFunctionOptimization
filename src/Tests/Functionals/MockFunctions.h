#pragma once

#include <gmock/gmock.h>

#include "Functions/IFunction.h"

class MockDifferentiableFunction : public Functions::IDifferentiableFunction
{
public:
    MOCK_METHOD(
        double,
        Value,
        (const Vector& point),
        (override)
    );

    MOCK_METHOD(
        Vector,
        Gradient,
        (const Vector& point),
        (override)
    );
};

class MockFunction : public Functions::IFunction
{
public:
    MOCK_METHOD(
        double,
        Value,
        (const Vector& point),
        (override)
    );
};
