cmake_minimum_required(VERSION 3.9.2)
project(demo)

set(CMAKE_CXX_STANDARD 11)

find_package(eddl)

add_executable(onnx_pointer 1_onnx_pointer.cpp)
target_link_libraries(onnx_pointer eddl)

add_executable(onnx_export 2_onnx_save_net_to_file.cpp)
target_link_libraries(onnx_export eddl)

add_executable(onnx_import 3_onnx_import_net_from_file.cpp)
target_link_libraries(onnx_import eddl)
