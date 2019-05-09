// This file is part of EDDLL an European Distributed Deep Learning Library.
// Developed within the DeepHealth project.
// Boosting AI in Europe.
//
// The MIT License (MIT)
//
// Copyright (c) 2019
//           Roberto Paredes Palacios, <rparedes@dsic.upv.es>
//           Jon Ander Gómez, <jon@dsic.upv.es>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Sofºtware, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#ifndef _EDDL_
#define _EDDL_

#include <initializer_list>
#include <vector>
#include "net.h"
#include "callbacks.h"
#include "initializers.h"

#define tensor LTensor*
#define layer Layer*
#define model Net*
#define optimizer optim*
#define callback Callback*
#define initializer Initializer*
#define compserv CompServ*

typedef vector<LTensor *> vltensor;

class EDDL {
public:
    // Create Tensors
    static tensor T(const initializer_list<int> &init);

    static tensor T(const shape s);

    static tensor T(string fname);


    //Operations tensors
    static void div(tensor t, float v);


    // Create Layers
    static layer Input(tensor t);
    static layer Input(const initializer_list<int> &init);

    static layer Embedding(int input_dim, int output_dim, string name); //Todo: Implement

    static layer Dense(layer parent, int ndim);
    static layer Dense(layer parent, int ndim, string name);
    static layer Dense(layer parent, int ndim, string name, bool use_bias); //Todo: Implement

    static layer Conv(layer parent, const initializer_list<int> &ks);
    static layer Conv(layer parent, const initializer_list<int> &ks, const initializer_list<int> &st, string p);
    static layer Conv(layer parent, const initializer_list<int> &ks, const initializer_list<int> &st);
    static layer Conv(layer parent, const initializer_list<int> &ks, string p);
    static layer Conv(layer parent, int filters, const initializer_list<int> &kernel_size, string padding,
                      const initializer_list<int> &strides, int groups, const initializer_list<int> &dilation_rate,
                      bool use_bias, string name); //Todo: Implement

    static layer DeConv(layer parent, int filters, const initializer_list<int> &kernel_size, string padding,
                        const initializer_list<int> &output_padding, const initializer_list<int> &dilation_rate,
                        const initializer_list<int> &strides, bool use_bias, string name); //Todo: Implement

    static layer UpSampling(layer parent, const initializer_list<int> &size, string interpolation,
                            string name); //Todo: Implement

    static layer MPool(layer parent, const initializer_list<int> &ks);
    static layer MPool(layer parent, const initializer_list<int> &ks, const initializer_list<int> &st, string p);
    static layer MPool(layer parent, const initializer_list<int> &ks, const initializer_list<int> &st);
    static layer MPool(layer parent, const initializer_list<int> &ks, string p);

    static layer Activation(layer parent, string act);
    static layer Activation(layer parent, string act, string name);

    static layer Reshape(layer parent, const initializer_list<int> &init);
    static layer Reshape(layer parent, const initializer_list<int> &init, string name);

    static layer Transpose(layer parent, const initializer_list<int> &dims, string name, int d); //Todo: Implement

    static layer Drop(layer parent, float df);
    static layer Drop(layer parent, float df, string name);
    static layer Dropout(layer parent, float rate, string name, int d); //Todo: Implement

    static layer BatchNormalization(layer parent, float momentum, float epsilon, bool affine,
                                    string name); //Todo: Implement

    static layer GaussianNoise(layer parent, float stddev, string name); //Todo: Implement

    //Todo: Implement -> static layer MaxPool(layer parent,const initializer_list<int>& pool_size,const initializer_list<int>& strides,string padding,string name);
    static layer GlobalMaxPool(layer parent, string name); //Todo: Implement

    static layer AveragePool(layer parent, const initializer_list<int> &pool_size, const initializer_list<int> &strides,
                             string padding, string name); //Todo: Implement

    static layer GlobalAveragePool(layer parent, string name); //Todo: Implement


    // ---- MERGE LAYERS ----
    static layer Add(const initializer_list<layer> &init);
    static layer Add(const initializer_list<layer> &init, string name);

    static layer Substract(const initializer_list<layer> &layers, string name); //Todo: Implement

    static layer Cat(const initializer_list<layer> &init);
    static layer Cat(const initializer_list<layer> &init, string name);
    //Todo: Implement -> static layer Concat(const initializer_list<layer>& layers,string name);

    static layer MatMul(const initializer_list<layer> &layers, string name); //Todo: Implement
    static layer Average(const initializer_list<layer> &layers, string name); //Todo: Implement
    static layer Maximum(const initializer_list<layer> &layers, string name); //Todo: Implement
    static layer Minimum(const initializer_list<layer> &layers, string name); //Todo: Implement


    // ---- OPTIMIZERS ----
    static optimizer SGD(const initializer_list<float> &p);
    static optimizer SGD(float lr, float momentum, float weight_decay, bool nesterov); //Todo: Implement
    static optimizer Adam(float lr, float beta_1, float beta_2, float epsilon, float weight_decay,
                          bool amsgrad); //Todo: Implement
    static optimizer RMSprop(float lr, float alpha, float weight_decay, float momentum); //Todo: Implement
    static optimizer Adagrad(float lr, float epsilon, float weight_decay); //Todo: Implement
    static optimizer Adadelta(float lr, float rho, float epsilon, float weight_decay); //Todo: Implement
    static optimizer Adamax(float lr, float beta_1, float beta_2, float epsilon, float weight_decay); //Todo: Implement
    static optimizer Nadam(float lr, float beta_1, float beta_2, float epsilon, float schedule_decay); //Todo: Implement

    static void change(optimizer o, const initializer_list<float> &p);

    // ---- LR SCHEDULERS ----
    static callback StepLR(int step_size, float gamma, int last_epoch); //Todo: Implement
    static callback MultiStepLR(const initializer_list<int> &milestones, float gamma, int last_epoch); //Todo: Implement
    static callback ExponentialLR(float gamma, int last_epoch); //Todo: Implement
    static callback CosineAnnealingLR(int T_max, float eta_min, int last_epoch); //Todo: Implement
    static callback ReduceLROnPlateau(string metric, string mode, float factor, int patience, float threshold,
                                      string threshold_mode, int cooldown, float min_lr, float eps); //Todo: Implement

    // ---- INITIALIZERS ----
    static initializer Constant(float value); //Todo: Implement
    static initializer RandomNormal(float mean, float stddev, int seed); //Todo: Implement
    static initializer RandomUniform(float minval, float maxval, int seed); //Todo: Implement
    static initializer Identity(float gain); //Todo: Implement
    static initializer Orthogonal(float gain, int seed); //Todo: Implement
    static initializer GlorotNormal(float seed); //Todo: Implement
    static initializer GlorotUniform(float seed); //Todo: Implement


    // Create net
    static model Model(vlayer in, vlayer out);
    // cs
    ///////////
    compserv CS_CPU(int th);
    compserv CS_GPU(const initializer_list<int> &g);
    compserv CS_FGPA(const initializer_list<int> &f);

    // Layer operations
    static void set_trainable(layer l); //Todo: Implement

    // Net operations
    static void plot(model m, string fname);
    static void info(model m);
    static void summary(model m); //Todo: Implement
    static void build(model net, optimizer o, const initializer_list<string> &c, const initializer_list<string> &m);

    static void build(model net, optimizer o, const initializer_list<string> &c, const initializer_list<string> &m, CompServ *cs);

    static void
    fit(model m, const initializer_list<LTensor *> &in, const initializer_list<LTensor *> &out, int batch, int epochs);

    static void evaluate(model m, const initializer_list<LTensor *> &in, const initializer_list<LTensor *> &out);

    static void save_model(model m, string fname); //Todo: Implement
    static model load_model(string fname); //Todo: Implement
    static layer get_layer(model m, string layer_name); //Todo: Implement
    static void set_trainable(model m); //Todo: Implement
    static model zoo_models(string model_name); //Todo: Implement

    // data
    static void download_mnist();

    static void download_cifar10(); //Todo: Implement
    static void download_cifar100(); //Todo: Implement
};

extern EDDL eddl;

#endif
