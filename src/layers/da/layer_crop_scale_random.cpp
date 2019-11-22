/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.1
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <utility>

#include "layer_da.h"


using namespace std;

int LCropAndScaleRandom::total_layers = 0;

LCropAndScaleRandom::LCropAndScaleRandom(Layer *parent, vector<float> factor, string da_mode, string name, int dev) : LinLayer(name, dev) {
    if(name.empty()) this->name = "crop_scale" + to_string(++total_layers);

    input = parent->output;
    output = new Tensor(input->getShape(), dev);
    delta = parent->delta;

    // Params
    this->factor=factor;
    this->da_mode=da_mode;

    parent->addchild(this);
    addparent(parent);
}

LCropAndScaleRandom::~LCropAndScaleRandom()
{
    delta=nullptr;
}

// virtual
void LCropAndScaleRandom::resize(int batch){
    output->resize(batch);
}

void LCropAndScaleRandom::forward() {
    Tensor::crop_scale_random(this->input, this->output, this->factor, this->da_mode);
}

void LCropAndScaleRandom::backward() {

}


Layer *LCropAndScaleRandom::share(int c, int bs, vector<Layer *> p) {
    LCropAndScaleRandom *n = new LCropAndScaleRandom(p[0], this->factor, this->da_mode, "share_" + to_string(c) + name, dev);
    n->orig = this;

    // TODO: Implement

    return n;
}

Layer *LCropAndScaleRandom::clone(int c, int bs, vector<Layer *> p, int todev) {
    LCropAndScaleRandom *n = new LCropAndScaleRandom(p[0], this->factor, this->da_mode, "clone_" + to_string(todev) + name, todev);
    n->orig = this;

    // TODO: Implement

    return n;
}


string LCropAndScaleRandom::plot(int c) {
    string s;

    if (c) s = name + " [label=" + "\"" + name + "\",style=filled,fontsize=12,fillcolor=bisque4,shape=box]";
    else s = name + " [label=" + "\"" + name + "\",style=filled,fontsize=12,fillcolor=White,shape=box]";

    return s;
}