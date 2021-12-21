cmake_minimum_required(VERSION 3.0.0)

project(lib)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tinyPTC
                    "/usr/include/X11")

file(GLOB_RECURSE TINYPTC_SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyPTC/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyPTC/*.c")

add_library(tinyPTC ${TINYPTC_SOURCE_FILES})

target_include_directories(tinyPTC
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)