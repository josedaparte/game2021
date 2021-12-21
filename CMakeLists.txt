cmake_minimum_required(VERSION 3.0.0)

project(cppGame21 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/lib)

add_library(slotmap
    src/slotMap.h
    src/slotMap.cpp
)

target_include_directories(slotmap
    PUBLIC
        src
)

add_executable(cppGame21 main.cpp)

target_link_libraries(cppGame21 slotmap tinyPTC X11)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
