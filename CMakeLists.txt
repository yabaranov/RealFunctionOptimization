cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

project(RealFunctionOptimization)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_subdirectory(src/RealFunctionOptimizationLib)
add_subdirectory(src/Sample)

if (MSVC)
    set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sample)
endif()