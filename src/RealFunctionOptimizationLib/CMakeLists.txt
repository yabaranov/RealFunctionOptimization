set(PROJECT_NAME RealFunctionOptimizationLib)

file(GLOB_RECURSE LIB_SOURCES "*.cpp")
file(GLOB_RECURSE LIB_HEADERS "*.h")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${LIB_SOURCES} ${LIB_HEADERS})

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES} ${LIB_HEADERS})

target_include_directories(${PROJECT_NAME}
  PUBLIC ../../third-party
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()
