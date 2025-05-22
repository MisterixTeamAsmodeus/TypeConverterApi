cmake_minimum_required(VERSION 3.10)

project(${type_converter_api_project_name}Test LANGUAGES CXX)

enable_testing()

file(GLOB_RECURSE SOURCE_FILES *.cpp)

if (NOT TARGET GTest::gtest_main)
    add_subdirectory(googletest)
endif ()

add_executable(
        ${PROJECT_NAME}
        ${SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ../include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${type_converter_api_project_name}
    GTest::gtest_main    # Google Test + main()
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})  # Автоматическая регистрация тестов