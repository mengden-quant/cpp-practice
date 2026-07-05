cmake_minimum_required(VERSION 3.23)

project(HW7ContainersTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    containers_tests
    test/sequential_container_tests.cpp
    test/list_type_container_tests.cpp
)

target_include_directories(
    containers_tests
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(
    containers_tests
    PRIVATE
        gtest
        gtest_main
)

add_test(
    NAME containers_tests
    COMMAND containers_tests
)

if (MSVC)
    target_compile_options(containers_tests PRIVATE /W4)
else()
    target_compile_options(containers_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()
