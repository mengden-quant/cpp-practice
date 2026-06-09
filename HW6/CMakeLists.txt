cmake_minimum_required(VERSION 3.5)

project(06.homework)

add_executable(containers sequential_container.hpp list_type_container.hpp main.cpp)
set_target_properties(containers PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
