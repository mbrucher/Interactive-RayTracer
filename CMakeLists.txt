cmake_minimum_required(VERSION 3.8)

project(IRT)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Eigen REQUIRED)
find_package(Boost REQUIRED unit_test_framework system)

enable_testing()

add_subdirectory(IRT)
add_subdirectory(tests)

