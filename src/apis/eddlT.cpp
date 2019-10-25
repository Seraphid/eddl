/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.1
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/


#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "eddlT.h"


using namespace std;

////////////////////////////////////////////////////////
///// EDDLT is a wrapper class to deal with Tensors
////////////////////////////////////////////////////////
namespace eddlT {


  // Creation ops ***********************************
  Tensor* create(const vector<int> &shape, float *ptr, int dev)
  {
    return new Tensor(shape,ptr,dev);
  }
  Tensor* create(const vector<int> &shape, int dev)
  {
    return new Tensor(shape,dev);
  }
  Tensor* create(const vector<int> &shape, float *ptr)
  {
    return new Tensor(shape,ptr);
  }

  Tensor* zeros(const vector<int> &shape, int dev)
  {
    return Tensor::zeros(shape,dev);
  }
  Tensor* ones(const vector<int> &shape, int dev){
    return Tensor::ones(shape,dev);
  }
  Tensor* full(const vector<int> &shape, float value, int dev){
    return Tensor::full(shape,value,dev);
  }
  Tensor* arange(float start, float end, float step, int dev){
    return Tensor::arange(start,end,step,dev);
  }
  Tensor* range(float start, float end, float step, int dev){
    return Tensor::range(start,end,step,dev);
  }
  Tensor* linspace(float start, float end, int steps, int dev){
    return Tensor::linspace(start,end,steps,dev);
  }
  Tensor* logspace(float start, float end, int steps, float base, int dev){
    return Tensor::logspace(start,end,steps,dev);
  }
  Tensor* eye(int size, int dev){
    return Tensor::eye(size,dev);
  }
  Tensor* randn(const vector<int> &shape, int dev){
    return Tensor::randn(shape,dev);
  }
  // Pointer functions ********************************
  float *getptr(Tensor *t){
    return t->ptr;
  }

  // Load from file ***********************************
  Tensor *load(string fname){
    FILE *fe = fopen(fname.c_str(), "rb");
    if (fe == nullptr) {
        fprintf(stderr, "%s not found\n", fname.c_str());
        exit(1);
    }

    vector<int> shape;
    int ndim,v;
    int read = fread(&ndim, sizeof(int), 1, fe);
    for (int i = 0; i < ndim; ++i) {
        int read = fread(&v, sizeof(int), 1, fe);
        shape.push_back(v);
    }

    Tensor *t=new Tensor(shape,DEV_CPU);
    t->load(fe);
    return t;
  }

  // Math ops       ***********************************
  void div_(Tensor *t,float f)
  {
    t->div_(f);
  }

}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
