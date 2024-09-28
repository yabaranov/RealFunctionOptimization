set(APP_NAME Sample)

file(GLOB_RECURSE APP_SOURCES "*.cpp")
file(GLOB_RECURSE APP_HEADERS "*.h")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${APP_SOURCES} ${APP_HEADERS})

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_HEADERS})

target_link_libraries(${APP_NAME} RealFunctionOptimizationLib)

target_compile_features(${APP_NAME} PRIVATE cxx_std_20)

if (MSVC)
    target_compile_options(${APP_NAME} PRIVATE /MP)
endif()