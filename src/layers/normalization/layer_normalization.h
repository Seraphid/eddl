/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.3
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/


#ifndef EDDL_LAYER_NORMALIZATION_H
#define EDDL_LAYER_NORMALIZATION_H

#include <string>
#include <stdio.h>

#include "../layer.h"
#include "../core/layer_core.h"
#include "../../regularizers/regularizer.h"

#define TRMODE 1
#define TSMODE 0

using namespace std;

void BN_forward(Tensor *input,Tensor *output, MapReduceDescriptor *MD, Tensor *bn_mean, Tensor *bn_var, Tensor *mean, Tensor *variance,float momentum, float epsilon, bool affine, Tensor *bn_g, Tensor *bn_b, Tensor *opa, int trmode);
void BN_backward(Tensor* input, Tensor *delta,Tensor *pdelta, MapReduceDescriptor *MD, Tensor *bn_mean, Tensor *bn_var, Tensor *mean, Tensor *variance,float epsilon, bool affine, Tensor *bn_g, Tensor *bn_b, Tensor *gbn_g, Tensor* gbn_b, Tensor *opa);



/// BatchNormalization Layer
class LBatchNorm : public LinLayer {
public:
    float momentum;
    float epsilon;
    bool affine;
    Tensor *mean;
    Tensor *variance;
    Tensor *bn_mean;
    Tensor *bn_var;
    Tensor *bn_g;
    Tensor *bn_b;
    Tensor *gbn_g;
    Tensor *gbn_b;
    Tensor *opa; //output pre-affine


    MapReduceDescriptor *MD;
    bool init;
    vector<int> axis;
    vector<int> shape;

    static int total_layers;
    vector<Layer *> layers;

    LBatchNorm(Layer *parent, float momentum, float epsilon, bool affine, string name, int dev, int mem);

    Layer *share(int c, int bs, vector<Layer *> p) override;

    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;

    void forward() override;

    void backward() override;

    void initialize() override;

    void resize(int batch) override;
    int get_trainable_params_count() override;

    string plot(int c) override;
};

/// LayerNormalization Layer
class LLayerNorm : public LinLayer {
public:
    float momentum;
    float epsilon;
    bool affine;
    Tensor *mean;
    Tensor *variance;
    Tensor *bn_mean;
    Tensor *bn_var;
    Tensor *bn_g;
    Tensor *bn_b;
    Tensor *gbn_g;
    Tensor *gbn_b;
    Tensor *opa; //output pre-affine

    PermuteDescriptor *PD;
    PermuteDescriptor *PD2;
    MapReduceDescriptor *MD;

    bool init;
    vector<int> axis;
    vector<int> shape;

    static int total_layers;
    vector<Layer *> layers;

    LLayerNorm(Layer *parent, float momentum, float epsilon, bool affine, string name, int dev, int mem);

    Layer *share(int c, int bs, vector<Layer *> p) override;

    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;

    void forward() override;

    void backward() override;

    void initialize() override;

    void resize(int batch) override;
    int get_trainable_params_count() override;

    string plot(int c) override;
};

/// GroupNormalization Layer
class LGroupNorm : public LinLayer {
public:
    float momentum;
    float epsilon;
    int groups;
    int N,CH,H,W;
    bool affine;
    Tensor *mean;
    Tensor *variance;
    Tensor *bn_mean;
    Tensor *bn_var;
    Tensor *bn_g;
    Tensor *bn_b;
    Tensor *gbn_g;
    Tensor *gbn_b;
    Tensor *opa; //output pre-affine

    PermuteDescriptor *PD;
    PermuteDescriptor *PD2;
    MapReduceDescriptor *MD;

    bool init;
    vector<int> axis;
    vector<int> shape;

    static int total_layers;
    vector<Layer *> layers;

    LGroupNorm(Layer *parent, int g, float momentum, float epsilon, bool affine, string name, int dev, int mem);

    Layer *share(int c, int bs, vector<Layer *> p) override;

    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;

    void forward() override;

    void backward() override;

    void initialize() override;

    void resize(int batch) override;
    int get_trainable_params_count() override;

    string plot(int c) override;
};


/// Normalization Layer
class LNorm : public LinLayer {
public:
    float epsilon;
    static int total_layers;
    vector<Layer *> layers;

    LNorm(Layer *parent, float epsilon,  string name, int dev, int mem);

    Layer *share(int c, int bs, vector<Layer *> p) override;

    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;

    void forward() override;

    void backward() override;

    void mem_delta() override;
    void free_delta() override;

    void resize(int batch) override;

    void reset() override;

    string plot(int c) override;
};

class LNormMax : public LinLayer {
public:
    float epsilon;
    static int total_layers;
    vector<Layer *> layers;

    LNormMax(Layer *parent, float epsilon,  string name, int dev, int mem);

    Layer *share(int c, int bs, vector<Layer *> p) override;

    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;

    void forward() override;

    void backward() override;

    void mem_delta() override;
    void free_delta() override;

    void resize(int batch) override;

    void reset() override;

    string plot(int c) override;
};


class LNormMinMax : public LinLayer {
public:
    float epsilon;
    static int total_layers;
    vector<Layer *> layers;

    LNormMinMax(Layer *parent, float epsilon,  string name, int dev, int mem);

    Layer *share(int c, int bs, vector<Layer *> p) override;

    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;

    void forward() override;

    void backward() override;

    void mem_delta() override;
    void free_delta() override;

    void resize(int batch) override;

    void reset() override;

    string plot(int c) override;
};

#endif //EDDL_LAYER_NORMALIZATION_H
