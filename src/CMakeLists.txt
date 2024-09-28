cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

project(RealFunctionOptimization)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_subdirectory(RealFunctionOptimizationLib)
add_subdirectory(Sample)