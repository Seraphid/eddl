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

#include "layer_pool.h"


using namespace std;


// ---- MAXPOOL2D ----
// constructors and clones

// constructors and clones
LMaxPool::LMaxPool(Layer *parent, const vector<int> &pool_size, const vector<int> &strides, string padding, string name, int dev, int mem) : LMaxPool(parent, new PoolDescriptor(pool_size, strides, padding, mem), name, dev, mem) {}

LMaxPool::LMaxPool(Layer *parent, const vector<int> &pool_size, const vector<int> &strides, const vector<int> &padding, string name, int dev, int mem) : LMaxPool(parent, new PoolDescriptor(pool_size, strides, padding, mem), name, dev, mem) {}

LMaxPool::LMaxPool(Layer *parent, PoolDescriptor *D, string name, int dev, int mem) : LPool(parent, D, name, dev, mem) {
    // Params
    D->indX = new Tensor(D->O->shape, dev);
    D->indY = new Tensor(D->O->shape, dev);
}


void LMaxPool::resize(int batch){
  //cout<<"Resize "<<name<<"\n";

  LPool::resize(batch);

  delete pd->indX;
  delete pd->indY;

  pd->indX = new Tensor(pd->O->shape, dev);
  pd->indY = new Tensor(pd->O->shape, dev);

}

void LMaxPool::forward() {
    MPool2D(this->pd);
}

void LMaxPool::backward() {
    MPool2D_back(this->pd);
}

Layer *LMaxPool::share(int c, int bs, vector<Layer *> p) {
    LMaxPool *n = new LMaxPool(p[0], vector<int>{pd->kr, pd->kc}, vector<int>{pd->sr, pd->sc}, pd->pad, "share_" + to_string(c) + this->name, this->dev, this->mem_level);
    n->orig = this;

    return n;
}

Layer *LMaxPool::clone(int c, int bs, vector<Layer *> p, int todev) {
    LMaxPool *n = new LMaxPool(p[0], vector<int>{pd->kr, pd->kc}, vector<int>{pd->sr, pd->sc}, pd->pad,
                           "clone_" + to_string(todev) + name, todev,mem_level);
    n->orig = this;

    return n;
}

string LMaxPool::plot(int c) {
    string s;

    if (c) s = name + " [label=" + "\"" + name + "\",style=filled,fontsize=12,fillcolor=gray,shape=box]";
    else s = name + " [label=" + "\"" + name + "\",style=filled,fontsize=12,fillcolor=gray75,shape=box]";

    return s;
}
