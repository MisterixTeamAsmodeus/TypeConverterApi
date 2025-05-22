cmake_minimum_required(VERSION 3.10)

set(type_converter_api_project_name TypeConverterApi)
project(${type_converter_api_project_name} LANGUAGES CXX)

option(ENABLE_TYPE_CONVERTER_API_QT "Включить поддержку Qt типов в библиотеки" OFF)

file(GLOB_RECURSE HEADER_FILES include/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_subdirectory(tests)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}
)

if (ENABLE_TYPE_CONVERTER_API_QT)
    target_compile_definitions(${PROJECT_NAME} PUBLIC USE_TYPE_QT)
    add_definitions(-DUSE_TYPE_QT)

    find_package(Qt5 COMPONENTS Core REQUIRED)

    target_link_libraries(${PROJECT_NAME} PUBLIC
            Qt5::Core
    )
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY include
        DESTINATION include
)