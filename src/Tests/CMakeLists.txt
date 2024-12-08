project(Test)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} main.cpp
    Functions/LineFunctionBaseTests.cpp
    Functions/LineFunctionTests.cpp
    Functions/InterpolationSplineBaseTests.cpp
    Functions/PolynomialFunctionTests.cpp
    Functionals/L1NormDifferenceFunctionalTests.cpp
    Functionals/MockFunctions.h
    Functionals/LInfNormDifferenceFunctionalTests.cpp
    Functionals/L2NormDifferenceFunctionalTests.cpp
    Functionals/MonteCarloIntegralFunctionalTests.cpp
    Optimizators/GaussNewtonOptimizatorTests.cpp
    Optimizators/GradientDescentOptimizatorTests.cpp
    Optimizators/MonteCarloOptimizatorTests.cpp
    Optimizators/OptimizatorsTestsCommon.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    RealFunctionOptimizationLib
    gtest
    gtest_main
    gmock
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)   
endif()
