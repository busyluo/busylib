cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(..)
link_libraries(busylib_base)

add_executable(logger_ut logger_ut.cc)
add_executable(base_ut base_ut.cc)
