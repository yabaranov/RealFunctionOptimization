set(PROJECT_NAME Sample)

file(GLOB_RECURSE APP_SOURCES "*.cpp")
file(GLOB_RECURSE APP_HEADERS "*.h")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${APP_SOURCES} ${APP_HEADERS})

add_executable(${PROJECT_NAME} ${APP_SOURCES} ${APP_HEADERS})

target_link_libraries(${PROJECT_NAME} RealFunctionOptimizationLib)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()