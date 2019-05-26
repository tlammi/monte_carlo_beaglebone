cmake_minimum_required (VERSION 3.12)
project(MonteCarlo)

add_definitions(-std=c++11)
include_directories("${PROJECT_SOURCE_DIR}/include")
configure_file(
    "${PROJECT_SOURCE_DIR}/include/buildcntrl.hpp.in"
    "${PROJECT_SOURCE_DIR}/include/buildcntrl.hpp"

)

add_subdirectory(src)
add_subdirectory(test)
