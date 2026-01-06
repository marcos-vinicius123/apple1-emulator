cmake_minimum_required(VERSION 3.10.0)
project(emulator VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)
    
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

add_executable(emulator ${all_SRCS})
