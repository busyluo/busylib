cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)

project(busylib)

#aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME}  ${SRC_LIST})

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory("busylib")
add_subdirectory("test")
