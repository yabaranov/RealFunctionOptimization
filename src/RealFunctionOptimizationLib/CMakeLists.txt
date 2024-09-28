set(LIB_NAME RealFunctionOptimizationLib)

file(GLOB_RECURSE LIB_SOURCES "*.cpp")
file(GLOB_RECURSE LIB_HEADERS "*.h")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${LIB_SOURCES} ${LIB_HEADERS})

add_library(${LIB_NAME} STATIC ${LIB_SOURCES} ${LIB_HEADERS})

target_include_directories(${LIB_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/third-party
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${LIB_NAME} PRIVATE cxx_std_20)

if (MSVC)
    target_compile_options(${LIB_NAME} PRIVATE /MP)
endif()
