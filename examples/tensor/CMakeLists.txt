cmake_minimum_required(VERSION 3.9.2)
project(demo)

set(CMAKE_CXX_STANDARD 11)

find_package(eddl)

add_executable(tensor_ops eddl_ops.cpp)
target_link_libraries(tensor_ops eddl)

add_executable(tensor_image eddl_image.cpp)
target_link_libraries(tensor_image eddl)

add_executable(tensor_io eddl_io.cpp)
target_link_libraries(tensor_io eddl)

add_executable(tensor_tests_dev eddl_tests_dev.cpp)
target_link_libraries(tensor_tests_dev eddl)
