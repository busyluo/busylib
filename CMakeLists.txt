cmake_minimum_required(VERSION 2.8)

project(busylib_proj)

#aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME}  ${SRC_LIST})

#set_target_properties(${PROJECT_NAME} PROPERTIES
#    CXX_STANDARD 11
#    CXX_STANDARD_REQUIRED YES
#    CXX_EXTENSIONS NO
#)

add_subdirectory("busylib")
add_subdirectory("test")
