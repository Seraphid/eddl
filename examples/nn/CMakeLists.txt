cmake_minimum_required(VERSION 3.9.2)
project(demo)

set(CMAKE_CXX_STANDARD 11)

find_package(eddl)


# EXAMPLES: MNIST ****************************************************
add_executable(mnist_mlp 1_mnist/1_mnist_mlp.cpp)
target_link_libraries(mnist_mlp eddl)

add_executable(mnist_mlp_initializers 1_mnist/2_mnist_mlp_initializers.cpp)
target_link_libraries(mnist_mlp_initializers eddl)

add_executable(mnist_mlp_regularizers 1_mnist/3_mnist_mlp_regularizers.cpp)
target_link_libraries(mnist_mlp_regularizers eddl)

add_executable(mnist_mlp_da 1_mnist/4_mnist_mlp_da.cpp)
target_link_libraries(mnist_mlp_da eddl)

add_executable(mnist_mlp_train_batch 1_mnist/5_mnist_mlp_train_batch.cpp)
target_link_libraries(mnist_mlp_train_batch eddl)

add_executable(mnist_auto_encoder 1_mnist/6_mnist_auto_encoder.cpp)
target_link_libraries(mnist_auto_encoder eddl)

add_executable(mnist_conv 1_mnist/7_mnist_conv.cpp)
target_link_libraries(mnist_conv eddl)


# EXAMPLES: CIFAR10 ****************************************************
add_executable(cifar_conv 2_cifar10/1_cifar_conv.cpp)
target_link_libraries(cifar_conv eddl)

add_executable(cifar_conv_da 2_cifar10/2_cifar_conv_da.cpp)
target_link_libraries(cifar_conv_da eddl)

add_executable(cifar_vgg16 2_cifar10/3_cifar_vgg16.cpp)
target_link_libraries(cifar_vgg16 eddl)

add_executable(cifar_vgg16_bn 2_cifar10/4_cifar_vgg16_bn.cpp)
target_link_libraries(cifar_vgg16_bn eddl)

add_executable(cifar_vgg16_gn 2_cifar10/4_cifar_vgg16_gn.cpp)
target_link_libraries(cifar_vgg16_gn eddl)

add_executable(cifar_resnet 2_cifar10/5_cifar_resnet.cpp)
target_link_libraries(cifar_resnet eddl)

add_executable(cifar_resnet_da_bn 2_cifar10/6_cifar_resnet_da_bn.cpp)
target_link_libraries(cifar_resnet_da_bn eddl)

add_executable(cifar_resnet50 2_cifar10/7_cifar_resnet50_da_bn.cpp)
target_link_libraries(cifar_resnet50 eddl)


# EXAMPLES: Drive segmentation ****************************************************
add_executable(drive_seg 3_drive/1_drive_seg.cpp)
target_link_libraries(drive_seg eddl)
