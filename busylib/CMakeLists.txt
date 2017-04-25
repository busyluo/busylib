cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(busylib)
#AUX_SOURCE_DIRECTORY(. LIB_SRCS)
#ADD_LIBRARY(${PROJECT_NAME} STATIC  ${LIB_SRCS})

INCLUDE_DIRECTORIES(.)

add_subdirectory("base")
add_subdirectory("net")
add_subdirectory("util")
add_subdirectory("3rdparty")
