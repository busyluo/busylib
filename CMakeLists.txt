cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)

project(busylib)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory("busylib")
add_subdirectory("test")
#add_subdirectory("example")
