cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

project(RealFunctionOptimization)

set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")


add_subdirectory(RealFunctionOptimizationLib)
add_subdirectory(Sample)