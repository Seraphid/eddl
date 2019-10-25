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
#include <ctime>
#include <limits>

#include "apis/eddlT.h"

using namespace std;
using namespace eddlT;

int main(int argc, char **argv) {
    int dev = DEV_GPU;

    tensor T=randn({5,5},dev);
    print(T);

    tensor Tn=normalize(T,0,1);
    normalize_(T,0,1);

    print(Tn);
    print(T);

    tensor U=randn({5,2},dev);
    print(U);

    tensor V=mult2D(T,U);
    info(V);
    print(V);

    ToCPU_(V);
    info(V);
    print(V);

    ToGPU_(V);
    info(V);
    print(V);

    Tensor * Vc=ToCPU(V);
    info(Vc);
    print(Vc);

    Tensor * Vg=ToGPU(Vc);
    info(Vg);
    print(Vg);

    Tensor  *V2=clone(V);
    info(V2);
    print(V2);


}
  
