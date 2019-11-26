/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.2
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/


#ifndef EDDL_LAYER_POOL_H
#define EDDL_LAYER_POOL_H


#include <string>
#include <stdio.h>

#include "../layer.h"

#define TRMODE 1
#define TSMODE 0

using namespace std;


/// Pool2D Layer
class LPool : public LinLayer {
public:
    static int total_layers;
    PoolDescriptor *pd;

    // constructors
    LPool(Layer *parent, PoolDescriptor *cd, string name, int dev);

    void resize(int batch) override;
};

/// MaxPool2D Layer
class LMaxPool : public LPool {
public:

    // constructors and clones
    LMaxPool(Layer *parent, const vector<int> &ks, const vector<int> &st, string p, string name, int d);

    LMaxPool(Layer *parent, const vector<int> &ks, const vector<int> &st, const vector<int> &p, string name, int dev);

    LMaxPool(Layer *parent, PoolDescriptor *cd, string name, int dev);

    // Params
    Tensor *indX, *indY;

    // implementation
    void forward() override;

    void backward() override;

    void resize(int batch) override;

    Layer *share(int c, int bs, vector<Layer *> p) override;

    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;

    string plot(int c) override;

};

/// AveragePool2D Layer
class LAveragePool : public LPool {
public:

    // constructors and clones
    LAveragePool(Layer *parent, const vector<int> &pool_size, const vector<int> &strides, string padding, string name, int dev);
    LAveragePool(Layer *parent, PoolDescriptor *D, string name, int dev);

//    // Params
//    Tensor *indX, *indY;
//
//    // implementation
//    void forward() override;
//
//    void backward() override;
//
//    Layer *share(int c, int bs, vector<Layer *> p) override;
//
//    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;
//
//    string plot(int c) override;

};

/// GlobalMaxPool2D Layer
class LGlobalMaxPool : public LPool {
public:

    // constructors and clones
    LGlobalMaxPool(Layer *parent, PoolDescriptor *D, string name, int dev);

//    // Params
//    Tensor *indX, *indY;
//
//    // implementation
//    void forward() override;
//
//    void backward() override;
//
//    Layer *share(int c, int bs, vector<Layer *> p) override;
//
//    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;
//
//    string plot(int c) override;

};

/// GlobalAveragePool2D Layer
class LGlobalAveragePool : public LPool {
public:

    // constructors and clones
    LGlobalAveragePool(Layer *parent, PoolDescriptor *D, string name, int dev);

//    // Params
//    Tensor *indX, *indY;
//
//    // implementation
//    void forward() override;
//
//    void backward() override;
//
//    Layer *share(int c, int bs, vector<Layer *> p) override;
//
//    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;
//
//    string plot(int c) override;

};

#endif //EDDL_LAYER_POOL_H
