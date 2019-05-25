cmake_minimum_required (VERSION 3.14)
project(MonteCarlo)

add_definitions(-std=c++11)
include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(src)
add_subdirectory(test)
