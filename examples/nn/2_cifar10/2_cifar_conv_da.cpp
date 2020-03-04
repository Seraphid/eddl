/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.3
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <eddl/apis/eddl.h>
#include <eddl/apis/eddlT.h>

using namespace eddl;

//////////////////////////////////
// cifar_conv_da.cpp:
// A very basic Conv for cifar10
// Data augmentation
// Using fit for training
//////////////////////////////////

int main(int argc, char **argv){

    // download CIFAR data
    download_cifar10();

    // Settings
    int epochs = 25;
    int batch_size = 100;
    int num_classes = 10;

    // network
    layer in=Input({3,32,32});
    layer l=in;

    // Data augmentation
//   l = RandomShift(l, {-0.2f, +0.2f}, {-0.2f, +0.2f});
//   l = RandomRotation(l, {-30.0f, +30.0f});
//   l = RandomScale(l, {0.85f, 2.0f});
//   l = RandomFlip(l, 1);
//   l = RandomCrop(l, {28, 28});
//   l = RandomCropScale(l, {0.f, 1.0f});
//   l = RandomCutout(l, {0.0f, 0.3f}, {0.0f, 0.3f});

    // l=Select(l, {"1", "1:31", "1:31"});
    l=MaxPool(ReLu(Conv(l,32,{3,3},{1,1})),{2,2});
    l=MaxPool(ReLu(Conv(l,64,{3,3},{1,1})),{2,2});
    l=MaxPool(ReLu(Conv(l,128,{3,3},{1,1})),{2,2});
    l=MaxPool(ReLu(Conv(l,256,{3,3},{1,1})),{2,2});

    l=Reshape(l,{-1});

    l=Activation(Dense(l,128),"relu");

    layer out=Activation(Dense(l,num_classes),"softmax");

    // net define input and output layers list
    model net=Model({in},{out});


    // Build model
    build(net,
          sgd(0.01, 0.9), // Optimizer
          {"soft_cross_entropy"}, // Losses
          {"categorical_accuracy"}, // Metrics
          CS_GPU({1}, "low_mem") // GPU with only one gpu
          //CS_CPU(-1, "low_mem")  // CPU with maximum threads availables
    );


    // plot the model
    plot(net,"model.pdf");

    // get some info from the network
    summary(net);

    // Load and preprocess training data
    tensor x_train = eddlT::load("cifar_trX.bin");
    tensor y_train = eddlT::load("cifar_trY.bin");
    eddlT::div_(x_train, 255.0);

    // Load and preprocess test data
    tensor x_test = eddlT::load("cifar_tsX.bin");
    tensor y_test = eddlT::load("cifar_tsY.bin");
    eddlT::div_(x_test, 255.0);

    for(int i=0;i<epochs;i++) {
        // training, list of input and output tensors, batch, epochs
        fit(net,{x_train},{y_train},batch_size, 1);
        // Evaluate train
        std::cout << "Evaluate test:" << std::endl;
        evaluate(net,{x_test},{y_test});
    }


}
