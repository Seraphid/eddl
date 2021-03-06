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

#include "loss.h"

using namespace std;

LHinge::LHinge() : Loss("hinge"){}

void LHinge::delta(Tensor *T, Tensor *Y, Tensor *D) {
}

float LHinge::value(Tensor *T, Tensor *Y) {
    return 0;
}
