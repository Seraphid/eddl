/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.3
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/

#ifndef EDDL_TENSOR_DESCRIPTORS_H
#define EDDL_TENSOR_DESCRIPTORS_H

#include <cstdio>
#include <vector>
#include <string>
#include <mutex>

#include <Eigen/Dense>


using namespace std;


class TensorDescriptor {
public:
    int device;

    int* cpu_addresses;
    int* gpu_addresses;
    int* fpga_addresses;

    TensorDescriptor(int dev=0);
    ~TensorDescriptor();

    // Don't mark as pure virtual because not all methods use the same parameters
    virtual void build(){};
    virtual void resize(int b){};
    void free_memory();
};

class SelDescriptor : public TensorDescriptor {

public:
    vector<int> ishape;
    vector<int> oshape;
    vector<vector<int>> idxs_range;


    vector<string> indices;

    SelDescriptor(int dev);
    SelDescriptor(const vector<string>& indices, int dev=0);

    virtual void build(vector<int> ishape);
    virtual void resize(int b);
    virtual void build_indices();
};

class PermuteDescriptor : public SelDescriptor {
public:
    vector<int> dims;

    PermuteDescriptor(const vector<int>& dims, int dev=0);
    
    void build(vector<int> ishape);
    void resize(int b);
    void build_indices();
};


#endif //EDDL_TENSOR_DESCRIPTORS_H
